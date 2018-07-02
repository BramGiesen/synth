#ifndef _H_SYNTH_
#define _H_SYNTH_

#include <iostream>
#include "math.h"

#include <string>
#include <sstream>
#include <vector>
#include <thread>
#include <unistd.h>
#include "jack_module.h"


class Synth {
public:
  Synth();
  virtual ~Synth();
  void setMidiPitch(float midiPitch);
  float getMidiPitch();
  void process();
  virtual double getSample() = 0;
  virtual void tick() = 0;

protected:
  void setFrequency(float frequency);
  virtual void updateFrequency() = 0;

  float mtof(float midiPitch);
  float samplerate;
  float frequency;
  JackModule jack;

private:
  float midiPitch;
};

#endif
