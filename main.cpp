#include <iostream>
#include <thread>

#include <unistd.h>
#include <stdio.h>

#include "jack_module.h"
#include "fmSynth.h"
#include "osc_server.h"
#include "osc.h"

#include <sstream>
#include <vector>


int main(int argc,char **argv)
{

  // recieve OSC
/******************************************************************************/
  int done = 0;
  localOSC osc;
  std::string serverport="7777";

  osc.init(serverport);
  osc.set_callback("/noteOn","iii");
  osc.set_callback("/MIDICC","sii");


  osc.start();

/******************************************************************************/
  //create a JackModule instance
  JackModule jack;

  // double samplerate = jack.getSamplerate();

  // init the jack, use program name as JACK client name
  jack.init(argv[0]);

  FmSynth fmSynth((float)jack.getSamplerate(), 60);

  std::thread t(&FmSynth::setUserInput, &fmSynth);

  //assign a function to the JackModule::onProces
  jack.onProcess = [&fmSynth](jack_default_audio_sample_t *inBuf,
     jack_default_audio_sample_t *outBuf, jack_nframes_t nframes)
  {
    //loop through frames, retrieve sample of sine per frame
    for(int i = 0; i < nframes; i++) {
      //TODO check type of jack_default_audio_sample_t, double? or float?
      outBuf[i] = fmSynth.getSample();// * env->process();
      fmSynth.tick();
    }

    return 0;
  };

  jack.autoConnect();

  //keep the program running and listen for user input, q = quit
  std::cout << "\n\nPress 'q' when you want to quit the program.\n";

  bool running = true;
  while (running)
  {
      //checks if fmSynth is still running, if fmSynth is done the program quits
      int run = fmSynth.getRunningStatus();

      int midiValue = osc.getMidiValue();
      fmSynth.setMidiPitch(midiValue);

      int envState = osc.getNoteOnOff();
      //
      if (envState > 0){
        fmSynth.setADSRgate(1);
        // std::cout << "envState = 1" << std::endl;
      }
      else {
        fmSynth.setADSRgate(0);
        // std::cout << "envState = 0" << std::endl;
      }

      if (run == 0){
        running = false;
        break;
      }

  }
  t.join();
  //end the program
  return 0;
} // main()
