#ifndef _H_SIMPLE_SYNTH_
#define _H_SIMPLE_SYNTH_

#include "synth.h"
#include "sineWave.h"
#include "ADSR.h"
#include "filter.h"

class FmSynth : public Synth {
public:
  //constructor
  FmSynth(float samplerate);
  FmSynth(float samplerate, float midiPitch);
  //prevent the default constructor to be generated
  FmSynth() = delete;
  //destructor
  ~FmSynth();
  //override base methods
  double getSample() override;
  void tick() override;
  void setADSR(int state);
  void setUserInput();
  int getRunningStatus();

protected:
  void updateFrequency() override;

private:

  bool running = true;
  bool getInput = true;

  ADSR *env = new ADSR();
  ADSR *env2 = new ADSR();
  Filter *filter = new Filter();
  SineWave sine;
  SineWave sine2;

  float amplitude = 1;
  int state = 0;
  float ratio = 1;
  float modDepth = 10;
  double freqModulator = frequency * ratio;

};

#endif
