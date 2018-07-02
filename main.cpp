#include <iostream>
#include <thread>
#include <unistd.h>
#include <stdio.h>
#include <sstream>
#include <vector>

#include "fmSynth.h"
#include "osc_server.h"
#include "osc.h"
#include "userInput.h"

bool running = true;

int main(int argc,char **argv)
{

  FmSynth fmSynth;

  //the user input class must control the fmsynth. therefore we make an instance of
  //UserInput with a reference of the fmSynth object
  UserInput userInput(fmSynth);

  //start a thread for commandline user input
  std::thread t1(&UserInput::getUserInput, &userInput);


  /******************************recieve OSC*************************************/
  //Initialize OSC communication to receive MIDI information
  LocalOSC osc(fmSynth);
  std::string serverport="7777";

  osc.init(serverport);
  //callback for midi note on and offs + pitch
  osc.set_callback("/noteOn","iii");

  osc.start();
  //start a thread to get midiInformation from the osc_client
  std::thread t2(&LocalOSC::getMIDIinfo, &osc);

  /******************************************************************************/
  //start running audio process function
  fmSynth.process();

  while (running)
  {
      //checks if fmSynth is still running, if fmSynth is done the program quits
      int run = fmSynth.getRunningStatus();

      if (run == 0){//running is falls when the getRunningStatus returns 0
        running = false;
        osc.programRunning = false;
        break;
      }

  }
  t1.join();
  t2.join();
  //end the program
  return 0;
} // main()
