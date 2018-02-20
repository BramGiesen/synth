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

  if(!msgpath.compare("/noteOn")){
     int channel = argv[0]->i;
     int pitch = argv[1]->i;
     int velocity = argv[2]->i;
     cout << "Message: " << channel << " " << pitch << " " << velocity << endl;

     if (pitch == midiSend && !first)
     {
     setMidiValue(pitch);
     setNoteOnOff(velocity);
     }
     else
     {
       if(velocity > 0){
       setMidiValue(pitch);
       }
       std::cout << "niet hetzelfde" << std::endl;
     }

     if (first)
     {
       setMidiValue(pitch);
       setNoteOnOff(velocity);
       first =  false;
     }

     if (velocity == 0)
     {
       std::cout << "first = true" << std::endl;
       first = true;
     }


     // setNoteOnOff(velocity);
   }

  return 0;
  } // realcallback()


  void localOSC::setMidiValue(int newMidiValue)
  {
    midiSend = newMidiValue;
  }

  int localOSC::getMidiValue()
  {
    return midiSend;
  }

  void localOSC::setNoteOnOff(int newVelocity)
  {
    velocity=newVelocity;
  }

  int localOSC::getNoteOnOff()
  {
    // std::cout << "noteOffinServer = " << velocity << std::endl;
    return velocity;
  }
