#include "synth.h"
#include <iostream>

Synth::Synth()
{

}

Synth::~Synth()
{

}

int Synth::mtof(int midiNote)
{
  semitone_ratio = pow(2, 1/12.0);
  c5 = 220.0 * pow(semitone_ratio, 3);
  c0 = c5 * pow(0.5, 5);

  frequency = c0 * pow(semitone_ratio, midiNote);
  return frequency;
}
