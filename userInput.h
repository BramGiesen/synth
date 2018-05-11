#ifndef _H_USERINPUT_
#define _H_USERINPUT_

#include "fmSynth.h"

class UserInput
{
public:
  UserInput(FmSynth&);
  ~UserInput();
  void getUserInput();
  void processInput(std::string line);
private:
  FmSynth& fmSynthRef;
  bool getInput = true;
  std::string inputLine;
  std::string inputWord;
  std::vector<std::string> userInputVec;
  std::vector<float> parameterVec;
};

#endif //_H_USERINPUT_
