#include "ADSR.h"
// #include <math.h>


ADSR::ADSR(void) {
    reset();
}

ADSR::~ADSR() {
}

void ADSR::setADSRrate(float newAttack, float newDecay, float newSustain, float newRelease)
{
  attackRate = newAttack;
  decayRate = newDecay * -1;
  sustainLevel = newSustain;
  releaseRate = newRelease * -1;
}

float ADSR::process() {
  	switch (state) {
          case env_idle:
              break;
          case env_attack:
              output = attackRate + output;

              if (output >= 1.0) {
                  output = 1.0;
                  state = env_decay;
              }
              break;
          case env_decay:
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

float ADSR::getOutput() {
	return output;
}
