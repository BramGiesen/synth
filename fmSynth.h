#ifndef _H_SIMPLE_SYNTH_
#define _H_SIMPLE_SYNTH_

#include "synth.h"
#include "sineWave.h"
#include "ADSR.h"
#include "filter.h"
#include "helpFile.h"


class FmSynth : public Synth {
public:
  FmSynth();
  FmSynth(float midiPitch);
  ~FmSynth();
  double getSample() override;
  void tick() override;

  void setEnvelope(int envelope, float attack, float decay, float sustain, float release);
  void setADSRgate(int state);
  void processInput(std::string line);
  void getUserInput();
  int getRunningStatus();

  // variables for fm-synthesis
  int totalOscillators;
  float amplitude = 0.5;
  int state = 0;
  float ratio = 0;
  float modDepth = 10;


  helpFile help;
  Filter *filter = new Filter("lowPass");
  bool running = true;

protected:
  void updateFrequency() override;

private:

  bool getInput = true;

//create instances
  Oscillator **oscillators;
  ADSR **envelopes;

// variables for ADSR
  int gate = 0;
  bool ADSRset = false;



};

#endif
