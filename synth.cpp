#include "synth.h"

/*---------------- CONSTRUCTORS / DESTRUCTOR ----------------*/
Synth::Synth(float samplerate)  : samplerate(samplerate), midiPitch(0)
{
    process();
    jack.init("fmSynth");
    jack.autoConnect();
  }

//destructor - delete s object, set pointer to nullptr
Synth::~Synth() {}

/*---------------- PUBLIC METHODS ----------------*/
//set the synth's pitch, using midi values.
void Synth::setMidiPitch(float midiPitch)
{
  //if midiPitch changes less then 1 cents, do not update the midiPitch
  if(midiPitch < (this->midiPitch - 0.005) || midiPitch > (this->midiPitch + 0.005)){
    this->midiPitch = midiPitch;
    setFrequency(mtof(midiPitch));
  } //end if
}

//returns the current midiPitch
float Synth::getMidiPitch()
{
  return midiPitch;
}

void Synth::process()
{

  //assign a function to the JackModule::onProces
  jack.onProcess = [&](jack_default_audio_sample_t *inBuf,
    jack_default_audio_sample_t *outBuf, jack_nframes_t nframes) {


      for(int i = 0; i < nframes; i++) {

        outBuf[i] = getSample();
        tick();
      }

      return 0;
    };
}

/*---------------- PROTECTED METHODS ----------------*/
//set the synth's frequency
void Synth::setFrequency(float frequency)
{
  //do not except frequencies below 0 and above nyquist
  if(frequency > 0 || frequency < 0.5 * samplerate) {
    this->frequency = frequency;
    //call updateFrequency method to allow derived classes to update frequency
    updateFrequency();
  }
  else {
    std::cout << "\nSynth::setFrequency - "
      << "values above nyquist aren't allowed\n";
  }
}


//translates midi to frequency
float Synth::mtof(float midiPitch)
{
  return pow(2.0,(midiPitch-69.0)/12.0) * 440.0;
}
