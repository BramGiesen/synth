#include "osc.h"


// subclass OSC into a local class so we can provide our own callback
class localOSC : public OSC
{
public:
  localOSC();
  ~localOSC();
  int realcallback(const char *path,const char *types,lo_arg **argv,int argc);
  int getMidiValue();
  int getNoteOnOff();
protected:
  void setMidiValue(int midiValue);
  void setNoteOnOff(int velocity);
private:
  bool first =  true;
  int midiSend = 0;
  int midiValue = 0;
  int velocity = 0;

};
