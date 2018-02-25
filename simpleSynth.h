#ifndef _H_SIMPLE_SYNTH_
#define _H_SIMPLE_SYNTH_

#include "synth.h"
#include "sine.h"
#include "ADSR.h"

class SimpleSynth : public Synth {
public:
  //constructor
  SimpleSynth(float samplerate);
  SimpleSynth(float samplerate, float midiPitch);
  //prevent the default constructor to be generated
  SimpleSynth() = delete;
  //destructor
  ~SimpleSynth();
  //override base methods
  double getSample() override;
  void tick() override;
  void setADSR(int state);

protected:
  void updateFrequency() override;

private:
  ADSR *env = new ADSR();
  ADSR *env2 = new ADSR();
  Sine sine;
  Sine sine2;
  int state = 0;
  float ratio = 1;
  float modDepth = 10;
  double freqModulator = frequency * ratio;

};

#endif
