#ifndef _SINEWAVE_H_
#define _SINEWAVE_H_
#include "oscillator.h"

class SineWave : public Oscillator
{
public:

  //constructors and destructor
  SineWave(double samplerate);
  SineWave(double samplerate, double frequency);
  SineWave(double samplerate, double frequency, double phase);
  ~SineWave();
  //prevent the default constructor to be generated
  SineWave() = delete;

  //override calculate
  //this method contains the sample calculation
  void calculate() override;

/*
  NOTE: we could use a seperate calculate method
  in that case -> overriding getSample is not necessary.
*/


};

#endif
