#ifndef _H_OSC_CLIENT_
#define _H_OSC_CLIENT_

#include <iostream>
#include <string>
#include <lo/lo.h>

#include <sstream>
#include <vector>

class OscClient
{
public:
  OscClient();
  ~OscClient();
  void sendNoteOn(int a, int b);
  void sendMidiCC(std::string param, std::string param1, std::string param2);
private:
  std::string param;
  std::string param1;
  std::string param2;
  lo_address target;
  std::string symbol;
};

#endif //_H_OSC_CLIENT_
