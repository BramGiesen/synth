#include "fmSynth.h"

/*---------------- CONSTRUCTORS / DESTRUCTOR ----------------*/
//constructor - calls the other constructor with midiPitch = 0
FmSynth::FmSynth(float samplerate)
  : FmSynth(samplerate, 0) {}

//using 0 as init value for midiPitch and sine frequency value
FmSynth::FmSynth(float samplerate, float midiPitch)
  : Synth(samplerate), sineCarrier(samplerate, 0), sineModulator(samplerate, 0) {

    setMidiPitch(midiPitch);

    // delay->setDelayTime(2);
    envelopeCarrier.setSampleRate(samplerate);
    envelopeCarrier.setADSRrate(0.1, 0.01, 0.9, 1);

    envelopeModulator.setSampleRate(samplerate);
    envelopeModulator.setADSRrate(0.1, 0.01, 0.9, 1);


  }

//destructor - delete s object, set pointer to nullptr
FmSynth::~FmSynth()
{
  delete filter;
  filter = nullptr;
}

/*---------------- PUBLIC METHODS ----------------*/
/*returns the current sample and in this function all the process functions are combined */
double FmSynth::getSample()
{
  return amplitude * delay.process(filter->lowHighPass(sineCarrier.getSample()) * envelopeCarrier.process());
}


/*tick function: sets the phase of the oscillator, the frequency is updated with each tick because the
frequency of the carrier is determined by the output of modulator wich changes with every tick() */
void FmSynth::tick() {
  sineModulator.tick();
  sineCarrier.tick();
  updateFrequency();
}

/*function that handles note-on and note-off mesages, of the gate is 1 the ADSR
is set to attack and then goes to the Decay and Sustain state, then it stays at the sustain state
 until the gate is set to 0 and then the release state is executed
*/
void FmSynth::setADSRgate(int state)
{
  this->state=state;

  if (state > 0){
    if(!ADSRset){
      envelopeCarrier.gate(true);
      envelopeModulator.gate(true);
    ADSRset = true;
    }
  }
  else {
    if(ADSRset){
      envelopeCarrier.gate(false);
      envelopeModulator.gate(false);
      ADSRset = false;
    }
  }
}

/* function that returns if the fm synth is still running, this bool is set in the userInput function,
if running is false the main function in main.cpp will return 0 and the program quits */
int FmSynth::getRunningStatus()
{
  return running;
}
/*---------------- PRIVATE METHODS ----------------*/
//set the synth's frequency
void FmSynth::updateFrequency() {
  sineModulator.setFrequency((double)frequency * ratio);
  sineCarrier.setFrequency((double)frequency + ((sineModulator.getSample() * envelopeModulator.process())* (modDepth * frequency * ratio)));
}
