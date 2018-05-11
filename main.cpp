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

  UserInput userInput(fmSynth);

  std::thread t1(&UserInput::getUserInput, &userInput);


  /******************************recieve OSC*************************************/
  int done = 0;
  LocalOSC osc(fmSynth);
  std::string serverport="7777";

  osc.init(serverport);
  osc.set_callback("/noteOn","iii");
  osc.set_callback("/MIDICC","sii");
  osc.start();

  std::thread t2(&LocalOSC::getMIDIinfo, &osc);

  /******************************************************************************/

  fmSynth.process();

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
  t1.join(); // joins the setUserInput thread in fmSynth
  t2.join(); // joins the setUserInput thread in fmSynth
  //end the program
  return 0;
} // main()
