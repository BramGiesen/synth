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
  void setADSRgate(int state);
  void setUserInput();
  int getRunningStatus();
  void setAdsrValue(std::string envelopeNumber, float attackRate,float decayRate,float sustainLevel,float releaseRate);

protected:
  void updateFrequency() override;

private:

  bool running = true;
  bool getInput = true;
//create instances
  ADSR envelopeCarrier;
  ADSR envelopeModulator;
  Filter *filter = new Filter();
  SineWave sineCarrier;
  SineWave sineModulator;

// variables for ADSR
  std::string envelopeNumber;
  float attackRate;
  float decayRate;
  float sustainLevel;
  float releaseRate;
  bool ADSRset = false;

// variables for fm-synthesis
  float amplitude = 1;
  int state = 0;
  float ratio = 0;
  float modDepth = 10;

};

#endif
