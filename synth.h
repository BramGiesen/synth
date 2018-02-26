#ifndef _H_SYNTH_
#define _H_SYNTH_

#include <iostream>
#include "math.h"

#include <string>
#include <sstream>
#include <vector>
#include <thread>
#include <unistd.h>


class Synth {
public:
  //constructor
  Synth(float samplerate);
  //prevent the default constructor to be generated
  Synth() = delete;
  //destructor
  virtual ~Synth();

  //set the pitch
  void setMidiPitch(float midiPitch);
  float getMidiPitch();
  //"pure virtual/abstract" methods, implement in derived classes
  //return the current sample
  virtual double getSample() = 0;
  virtual void tick() = 0;

protected:
  void setFrequency(float frequency);
  //"pure virtual/abstract" method, implement in derived classes
  virtual void updateFrequency() = 0;

  float mtof(float midiPitch);
  float samplerate;
  float frequency;
  std::string synthRatio = "nog niks";

private:
  float midiPitch;
};

#endif
