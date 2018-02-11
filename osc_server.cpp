#include "osc_server.h"


localOSC::localOSC()
{

}

localOSC::~localOSC()
{

}

int localOSC::realcallback(const char *path,const char *types,lo_arg **argv,int argc)
{
string msgpath=path;

  cout << "path: " << msgpath << endl;
  if(!msgpath.compare("/midiNote")){
    string paramname=(char *)argv[0];
    int int1 = argv[1]->i;
    int int2 = argv[2]->i;
    cout << "Message: " <<
      paramname << " " <<
      int1 << " " <<
      int2 << " " << endl;
      setMidiValue(int2);
  } 

  return 0;
  } // realcallback()


  void localOSC::setMidiValue(int newMidiValue)
  {
    midiValue=newMidiValue;
  }

  int localOSC::getMidiValue()
  {
    return midiValue;
  }
