#include "fmSynth.h"

/*---------------- CONSTRUCTORS / DESTRUCTOR ----------------*/
//constructor - calls the other constructor with midiPitch = 0
FmSynth::FmSynth(float samplerate)
  : FmSynth(samplerate, 0) {}

//using 0 as init value for midiPitch and sine frequency value
FmSynth::FmSynth(float samplerate, float midiPitch)
  : Synth(samplerate), sine(samplerate, 0), sine2(samplerate, 0) {
    //set midi pitch
    //(we can't do this is Synth constructor, because its derived class does not
    //exist yet, which we do need due to the abstract updateFrequency method
    setMidiPitch(midiPitch);

    env->setAttackRate(.001 * samplerate);  // .1 second
    env->setDecayRate(.3 * samplerate);
    env->setReleaseRate(1 * samplerate);
    env->setSustainLevel(.8);

    env2->setAttackRate(.1 * samplerate);  // .1 second
    env2->setDecayRate(.5 * samplerate);
    env2->setReleaseRate(1 * samplerate);
    env2->setSustainLevel(.9);


  }

//destructor - delete s object, set pointer to nullptr
FmSynth::~FmSynth()
{
    delete env;
    env = nullptr;
    delete env2;
    env2 = nullptr;
    delete filter;
    filter = nullptr;
}

/*---------------- PUBLIC METHODS ----------------*/
//returns the current sample
double FmSynth::getSample() {
  return amplitude * filter->lowPass(sine.getSample()) * env->process();
}

//TODO - should we add a clock object with listeners, instead of using tick?
//updates sample, 'tick'
void FmSynth::tick() {
  sine2.tick();
  sine.tick();
  updateFrequency();
  // std::cout << "state = " << env->getState() << std::endl;
}

void FmSynth::setADSR(int newState)
{
  state = newState;

  if (state > 0){
    env->gate(true);
    env2->gate(true);
    // std::cout << "envState = 1" << std::endl;
  }
  else {
    env->gate(false);
    env2->gate(false);
  //   std::cout << "envState = 0" << std::endl;
  }
}



/*---------------- PRIVATE METHODS ----------------*/
//set the synth's frequency
void FmSynth::updateFrequency() {
  sine2.setFrequency((double)frequency * ratio);
  sine.setFrequency((double)frequency + ((sine2.getSample() * env2->process())* (modDepth * frequency * ratio)));
}
