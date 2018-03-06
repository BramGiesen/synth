#include "ADSR.h"

ADSR::ADSR()
{
    reset();
}

ADSR::~ADSR() {
}

// is used to set the ADSR values, function is called in FmSynth.
void ADSR::setADSRrate(float newAttack, float newDecay, float newSustain, float newRelease)
{
  attackRate = 1 / newAttack / samplerate;
  decayRate = (newDecay * -1) / samplerate;
  sustainLevel = newSustain;
  releaseRate = (newRelease * -1) / samplerate;
}

/* proces function, output get multiplied with the signal, this happen in the getSample() of FmSynth.cpp.
attack and decay have a target value, if the value is reached it switches to the next state of the ADSR.
the release state is triggered by the gate() function wich is controlled in the setADSRgate() function in FmSynth. */

float ADSR::process() {
  	switch (state) {
          case env_idle:
              break;
          case env_attack:
              // std::cout << "attack = " << output << std::endl;
              output = attackRate + output;

              if (output >= 1.0) {
                  output = 1.0;
                  state = env_decay;
              }
              break;
          case env_decay:
              // std::cout << "decay = " << output << std::endl;
              output = decayRate + output;
              if (output <= sustainLevel) {
                  output = sustainLevel;
                  state = env_sustain;
              }
              break;
          case env_sustain:
              // std::cout << "sustain = " << output << std::endl;
              break;
          case env_release:
              // std::cout << "release = " << output << std::endl;
              output = releaseRate + output;
              if (output <= 0.0) {
                  output = 0.0;
                  state = env_idle;
              }
            }
	return output;
}

/* starts the envelope by setting it to it's first state; attack.
and stops the envelope by triggering the release state of the envelope. */
void ADSR::gate(int gate) {
	if (gate){
      state = env_attack;
    }
	else if (state != env_idle){
          state = env_release;
        }
}

int ADSR::getState() {
    return state;
}

void ADSR::reset() {
    state = env_idle;
    output = 0.0;
}

void ADSR::setSampleRate(float samplerate)
{
  this->samplerate = samplerate;
  std::cout << "samplerate = " << samplerate << std::endl;
}

float ADSR::getOutput() {
	return output;
}
