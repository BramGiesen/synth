#include "osc_client.h"

OscClient::OscClient()
{
  target = lo_address_new("localhost","7777");
}

OscClient::~OscClient()
{

}

void OscClient::thread_function()
{
  std::string line;
  std::string word;
  while(true){
    std::getline(std::cin, line);
    std::stringstream ss(line);

    std::vector<std::string> vec;

    while (getline(ss, word, ' ')) {
      vec.emplace_back(word);
    }

    if (vec[0] == "fm")
    {
      std::cout << vec[0] << vec[1] << vec[2] << std::endl;
      vec.clear();

    }
  }
}

void OscClient::sendNoteOn(int newA, int newB)
{
  a = newA;
  b = newB;

  lo_send(target,"/noteOn","iii",1,a,b);
}

void OscClient::sendMidiCC(std::string newParam ,std::string newParam1,std::string newParam2)
{
  param  = newParam;
  std::cout << param << " = message" << std::endl;
  // param1 = newParam1;
  // param2 = newParam2;
  // lo_send(target,"/MIDICC","sii", param , param1, param2);
}
