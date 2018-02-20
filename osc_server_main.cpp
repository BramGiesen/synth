#include <iostream>
#include <unistd.h>
#include <thread>
#include <math.h>
#include <stdio.h>

#include "osc_server.h"
#include "osc.h"

#include "jack_module.h"
#include "synth.h"
#include "ADSR.h"

#define PI_2 6.28318530717959

int main(int argc,char **argv)
{
  double samplerate = 44100;
// recieve OSC
/******************************************************************************/
  int done = 0;
  localOSC osc;
  std::string serverport="7777";

  osc.init(serverport);
  osc.set_callback("/noteOn","iii");


  osc.start();
  // std::cout << "Listening on port " << serverport << std::endl;

/******************************************************************************/

// create ADSR env
ADSR *env = new ADSR();

// initialize settings
env->setAttackRate(.001 * samplerate);  // .1 second
env->setDecayRate(.3 * samplerate);
env->setReleaseRate(1 * samplerate);
env->setSustainLevel(.8);

// at some point, by MIDI perhaps, the envelope is gated "on"
env->gate(true);
// and some time later, it's gated "off"
env->gate(false);

Synth synth;

/******************************************************************************/
// synthesis

//create a JackModule instance
JackModule jack;

// int initialize = jack.init();
//std::cout << initialize << std::endl;
int currentMidiValue = 0;

//assign a function to the JackModule::onProces
jack.onProcess = [&](jack_default_audio_sample_t *inBuf,
   jack_default_audio_sample_t *outBuf, jack_nframes_t nframes, double samplerate) {

  int midiValue = osc.getMidiValue();
  int envState = osc.getNoteOnOff();



  if (envState > 0){
    env->gate(true);
    // std::cout << "envState = 1" << std::endl;
  } else {
    env->gate(false);
    // std::cout << "envState = 0" << std::endl;
  }


  double frequency = synth.mtof(midiValue);
  static double depth = 10;
  float ratio = 2;

  static double phaseM = 0;
  double freqModulator = frequency * ratio;
  static double phase = 0;
  static double amplitude = 0.5;


  if(frequency < 9)
    amplitude = 0;
  else
    amplitude = 0.5;

  for(int i = 0; i < nframes; i++) {
    double sine = amplitude * sin(phase * PI_2);
    double sineM = sin(phaseM * PI_2);
    // std::cout << "sineM = " << sineM << std::endl;

    double square = sine;
    if(square>0.0)
      square = 0.3;
    else
      square = -0.3;

    outBuf[i] =  sine * env->process();

    // sineM = 1;
    phaseM += freqModulator / samplerate;

    double monitor = sineM * (depth * freqModulator);
    // std::cout << "monitor = " << monitor << std::endl;
    // phase += frequency * (sineM * depth) / samplerate;
    phase += (frequency + (sineM * (depth * freqModulator))) / samplerate;
  }

  return 0;
};

// init the jack, use program name as JACK client name
jack.init(argv[0]);
jack.autoConnect();

//keep the program running and listen for user input, q = quit
std::cout << "\n\nPress 'q' when you want to quit the program.\n";
bool running = true;
while (running)
{
    switch (std::cin.get())
    {
        case 'q':
          running = false;
          break;
    }
}



  while (!done)
  {
    usleep(1000);
  }

/******************************************************************************/


  return 0;
}
