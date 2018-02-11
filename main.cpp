#include <iostream>
#include <thread>
#include <math.h>
#include <stdio.h>

#include "jack_module.h"

#define PI_2 6.28318530717959



int main(int argc,char **argv)
{
  //create a JackModule instance
  JackModule jack;

  double frequency = 60;
  std::cout << frequency << std::endl;

  //int initialize = jack.init();
  //std::cout << initialize << std::endl;
  //assign a function to the JackModule::onProces
  jack.onProcess = [&](jack_default_audio_sample_t *inBuf,
     jack_default_audio_sample_t *outBuf, jack_nframes_t nframes, double samplerate) {

    static double depth = 80;
    static double phaseM = 0;
    static double frequencyM = 400;
    static double phase = 0;
    static double amplitude = 0.5;
    // static double frequency = 880;

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

  //end the program
  return 0;
} // main()
