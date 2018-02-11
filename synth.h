#ifndef _H_SYNTH_
#define _H_SYNTH_

#include <iostream>
#include <math.h>

class Synth
{
public:
  Synth();
  ~Synth();
int mtof(int midiNote);
private:
  int midiNote;
  double semitone_ratio;
  double c0;
  double c5;
  double frequency;
};


#endif//_H_SYNTH_
