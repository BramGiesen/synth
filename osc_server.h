#include "osc.h"


// subclass OSC into a local class so we can provide our own callback
class localOSC : public OSC
{
public:
  localOSC();
  ~localOSC();
  int realcallback(const char *path,const char *types,lo_arg **argv,int argc);
  int getMidiValue();
protected:
  void setMidiValue(int midiValue);
private:
  int midiValue = 0;
};
