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



int main(int argc,char **argv)
{
  //TODO replace samplerate funtion
  // FmSynth fmSynth((float)jack.getSamplerate(), 60);

  FmSynth fmSynth(44100, 60);

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
  //callback for midi controls, not implimented jet.
  osc.set_callback("/MIDICC","sii");
  osc.start();
  //start a thread to get midiInformation from the osc_client
  std::thread t2(&LocalOSC::getMIDIinfo, &osc);

  /******************************************************************************/
  //start running audio process function
  fmSynth.process();

  //  8888888888 888b     d888       .d8888b.                    888    888
  //  888        8888b   d8888      d88P  Y88b                   888    888
  //  888        88888b.d88888      Y88b.                        888    888
  //  8888888    888Y88888P888       "Y888b.   888  888 88888b.  888888 88888b.
  //  888        888 Y888P 888          "Y88b. 888  888 888 "88b 888    888 "88b
  //  888        888  Y8P  888            "888 888  888 888  888 888    888  888
  //  888        888   "   888      Y88b  d88P Y88b 888 888  888 Y88b.  888  888
  //  888        888       888       "Y8888P"   "Y88888 888  888  "Y888 888  888
  //                                                888
  //                                           Y8b d88P
  //                                            "Y88P"


  //keep the program running and listen for user input and OSC messages, q = quit
  std::cout << "\n\nPress 'q' when you want to quit the program.\n\n";
  std::cout << "type 'help' for commands\n" << std::endl;
  bool running = true;
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
