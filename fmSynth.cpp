#include "fmSynth.h"

FmSynth::FmSynth() : FmSynth(0)
{

}

FmSynth::FmSynth(float midiPitch) : Synth() {

    //set total number oscillators, in this case 1 modulator and 1 carrier
    totalOscillators = 2;
    //create 2 elements in list oscillators
    oscillators = new Oscillator*[totalOscillators];

    envelopes = new ADSR*[totalOscillators];

    //add to sine oscillators to the list
    for (int numberOscillators = 0; numberOscillators < totalOscillators;  numberOscillators++){
      oscillators[numberOscillators] = new SineWave(samplerate, 0, 0);
    }

    //add a envelope to each oscillator
    for (int numberEnvelopes = 0; numberEnvelopes < totalOscillators;  numberEnvelopes++){
      envelopes[numberEnvelopes] = new ADSR;
      envelopes[numberEnvelopes]->setSampleRate(samplerate);
      envelopes[numberEnvelopes]->setADSRrate(0.1, 0.01, 0.9, 1);
    }

    setMidiPitch(midiPitch);

  }

FmSynth::~FmSynth()
{
  delete filter;
  filter = nullptr;
  delete[] oscillators;
  oscillators = nullptr;
  delete[] envelopes;
  envelopes = nullptr;
}

/*returns the current sample and in this function all the process functions are combined */
double FmSynth::getSample()
{
  return amplitude * filter->lowHighPass(oscillators[0]->getSample()) * envelopes[0]->process();
}

void FmSynth::setEnvelope(int envelope, float attack, float decay, float sustain, float release)
{
    envelopes[envelope]->setADSRrate(attack, decay, sustain, release);
}


/*tick function: sets the phase of the oscillator, the frequency is updated with each tick because the
frequency of the carrier is determined by the output of modulator wich changes with every tick() */
void FmSynth::tick() {

  for (int index = 0; index < totalOscillators; index++){
    oscillators[index]->tick();
  }
  //update frequency for FM synthesis
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
      for(int index = 0; index < totalOscillators; index++)
        envelopes[index]->gate(true);
    ADSRset = true;
    }
  }
  else {
    if(ADSRset){
      for(int index = 0; index < totalOscillators; index++)
        envelopes[index]->gate(false);
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

/* this function sets the frequency of the carrier by getting a sample of the modulator and add
that value to the frequency of the carrier*/
void FmSynth::updateFrequency() {
  //modulator
  oscillators[1]->setFrequency((double)frequency * ratio);
  //carrier
  oscillators[0]->setFrequency((double)frequency + ((oscillators[1]->getSample() * envelopes[1]->process())* (modDepth * frequency * ratio)));
}
