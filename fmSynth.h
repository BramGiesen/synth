#ifndef _H_SIMPLE_SYNTH_
#define _H_SIMPLE_SYNTH_

#include "synth.h"
#include "sineWave.h"
#include "ADSR.h"
#include "filter.h"
#include "helpFile.h"


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
  void processInput(std::string line);
  void getUserInput();
  int getRunningStatus();

  // variables for fm-synthesis
  float amplitude = 0.5;
  int state = 0;
  float ratio = 0;
  float modDepth = 10;

  ADSR envelopeCarrier;
  ADSR envelopeModulator;

  helpFile help;
  Filter *filter = new Filter("lowPass");
  bool running = true;

protected:
  void updateFrequency() override;

private:

  bool getInput = true;

//create instances
  SineWave sineCarrier;
  SineWave sineModulator;

// variables for ADSR
  std::string envelopeNumber;
  int gate = 0;
  bool ADSRset = false;



};

#endif
