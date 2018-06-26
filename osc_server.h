#include "osc.h"
#include "fmSynth.h"


// subclass OSC into a local class so we can provide our own callback
class LocalOSC : public OSC
{
public:
  LocalOSC(FmSynth&);
  ~LocalOSC();
  int realcallback(const char *path,const char *types,lo_arg **argv,int argc);
  void getMidiValue();
  void getNoteOnOff();
  void getMIDIinfo();
  bool programRunning = true;
protected:
  void setMidiValue(int midiValue);
  void setNoteOnOff(int velocity);
private:
  FmSynth& fmSynthRef;
  bool first =  true;
  int gate = 0;
  int midiSend = 0;
  int velocity = 0;

};
