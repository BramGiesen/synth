#include "osc_client.h"

OscClient::OscClient()
{
  target = lo_address_new("localhost","7777");
}

OscClient::~OscClient()
{

}

void OscClient::sendNoteOn(int pitch, int velocity)
{
  lo_send(target,"/noteOn","iii",1, pitch, velocity);
}

void OscClient::sendMidiCC(std::string newParam ,std::string newParam1,std::string newParam2)
{
  param  = newParam;
  std::cout << param << " = message" << std::endl;
  // param1 = newParam1;
  // param2 = newParam2;
  // lo_send(target,"/MIDICC","sii", param , param1, param2);
}
