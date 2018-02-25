#ifndef _OSCILLATOR_H_
#define _OSCILLATOR_H_
#include <iostream>
#include "math.h"

#define PI_2 6.28318530717959

class Oscillator
{
public:
  //Constructor and destructor
  Oscillator(double samplerate, double frequency, double phase);
  virtual ~Oscillator();

  //return the current sample
  double getSample();
  void tick();

  //getters and setters
  void setFrequency(double frequency);
  double getFrequency();

  //NOTE - do we need a setter for phase? for now -> not using one

protected:
  //abstract method, calculate the next sample, implement in derived classes
  virtual void calculate() = 0;
  double frequency;
  //note: do we need a amplitude?
  double phase;
  double sample;
  double samplerate;



};

#endif
