#include "sine.h"

//Constructors and destructor
Sine::Sine(double samplerate) : Sine(samplerate, 0, 0) {}

Sine::Sine(double samplerate, double frequency) :
  Sine(samplerate, frequency, 0) {}

Sine::Sine(double samplerate, double frequency, double phase) :
  Oscillator (samplerate, frequency, phase) {}

Sine::~Sine() {}

//override calculate method
//this method contains the sample calculation
void Sine::calculate()
{
  //NOTE sin() method is not the most efficient way to calculate the sine value
  sample = sin(phase * PI_2 );
  //std::cout << "\n" << phase  << "PI_2 " << "\n" ;
}
