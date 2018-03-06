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
  int gate;

/******************************recieve OSC*************************************/
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
      outBuf[i] = fmSynth.process();
      fmSynth.tick();
      // fmSynth.getSample();// * env->process();
    }

    return 0;
  };

  jack.autoConnect();

  //keep the program running and listen for user input, q = quit
  std::cout << "\n\nPress 'q' when you want to quit the program.\n\n";
  std::cout << "type 'help' for commands\n" << std::endl;
  bool running = true;
  while (running)
  {

      int midiValue = osc.getMidiValue();
      fmSynth.setMidiPitch(midiValue);

      int envState = osc.getNoteOnOff();

      // sets state in FmSynth 1 = attack state of ADSR, 0 = release state
      gate = (envState > 0) ? 1 : 0;
      fmSynth.setADSRgate(gate);

      //checks if fmSynth is still running, if fmSynth is done the program quits
      int run = fmSynth.getRunningStatus();

      if (run == 0){//running is falls when the getRunningStatus returns 0
        running = false;
        break;
      }

  }
  t.join(); // joins the setUserInput thread in fmSynth
  //end the program
  return 0;
} // main()
