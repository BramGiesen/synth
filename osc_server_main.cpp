#include <iostream>
#include <unistd.h>
#include <thread>
#include <math.h>
#include <stdio.h>

#include "osc_server.h"
#include "osc.h"

#include "jack_module.h"
#include "synth.h"

#define PI_2 6.28318530717959

int main(int argc,char **argv)
{
// recieve OSC
/******************************************************************************/
  int done = 0;
  localOSC osc;
  std::string serverport="7777";

  osc.init(serverport);
  osc.set_callback("/midiNote","siii");


  osc.start();
  // std::cout << "Listening on port " << serverport << std::endl;

/******************************************************************************/

  Synth synth;

/******************************************************************************/
// synthesis

//create a JackModule instance
JackModule jack;

// int initialize = jack.init();
//std::cout << initialize << std::endl;


//assign a function to the JackModule::onProces
jack.onProcess = [&](jack_default_audio_sample_t *inBuf,
   jack_default_audio_sample_t *outBuf, jack_nframes_t nframes, double samplerate) {

  int midiValue = osc.getMidiValue();
  double frequency = synth.mtof(midiValue);
  static double depth = 30;
  static double phaseM = 0;
  static double frequencyM = frequency * 20;
  static double phase = 0;
  static double amplitude = 0.5;


  if(frequency < 9)
    amplitude = 0;
  else
    amplitude = 0.5;

  for(int i = 0; i < nframes; i++) {
    double sine = amplitude * sin(phase * PI_2);
    double sineM = amplitude * sin(phaseM * PI_2);

    double square = sine;
    if(square>0.0)
      square = 0.3;
    else
      square = -0.3;

    outBuf[i] =  sine;

    // sineM = 1;
    phaseM += frequencyM / samplerate;
    phase += (frequency + sineM * depth) / samplerate;
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
