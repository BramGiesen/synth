#include "oscillator.h"


//Constructor and destructor
Oscillator::Oscillator(double samplerate, double frequency, double phase) :
  frequency(frequency), phase(phase), sample(0), samplerate(samplerate)
{
  //TODO - use setFrequency and phase instead, to prevent outrange values
  std::cout << "\nInside Oscillator::oscillator (double frequency, double phase)"
    << "\nfrequency: " << frequency
    << "\nphase: " << phase;
    // initialize settings

}

Oscillator::~Oscillator()
{

}

double Oscillator::getSample() { return sample; }

void Oscillator::tick()
{
  phase += frequency / samplerate;
  // phase += (frequency + (sineModulator * (modDepth * frequency * ratio))) / samplerate;
  //wrap phase from 0 to 1
  // if(phase >= 1) phase = phase - 1;
  //calculate new sample
  calculate();
}

//
// void Oscillator::tick(double newSine)
// {
//   phase += frequency / samplerate;
//   // phase += (frequency + (sineModulator * (modDepth * frequency * ratio))) / samplerate;
//   //wrap phase from 0 to 1
//   if(phase >= 1) phase = phase - 1;
//   //calculate new sample
//   calculate();
// }


void Oscillator::setFrequency(double frequency)
{
  // if(frequency > 0 && frequency < 0.5 * samplerate)
  this->frequency = frequency;
}

double Oscillator::getFrequency() { return frequency; }
