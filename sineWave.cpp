#include "sineWave.h"

//Constructors and destructor
SineWave::SineWave(double samplerate) : SineWave(samplerate, 0, 0) {}

SineWave::SineWave(double samplerate, double frequency) :
  SineWave(samplerate, frequency, 0) {}

SineWave::SineWave(double samplerate, double frequency, double phase) :
  Oscillator (samplerate, frequency, phase) {}

SineWave::~SineWave() {}

//override calculate method
//this method contains the sample calculation
void SineWave::calculate()
{
  //NOTE sin() method is not the most efficient way to calculate the sine value
  sample = sin(phase * PI_2 );
  //std::cout << "\n" << phase  << "PI_2 " << "\n" ;
}
