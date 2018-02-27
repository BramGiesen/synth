#include "fmSynth.h"

/*---------------- CONSTRUCTORS / DESTRUCTOR ----------------*/
//constructor - calls the other constructor with midiPitch = 0
FmSynth::FmSynth(float samplerate)
  : FmSynth(samplerate, 0) {}

//using 0 as init value for midiPitch and sine frequency value
FmSynth::FmSynth(float samplerate, float midiPitch)
  : Synth(samplerate), sine(samplerate, 0), sine2(samplerate, 0) {

    setMidiPitch(midiPitch);

    env->setADSRrate(0.001, 0.0001, 0.9, 0.0001);
    env2->setADSRrate(0.001, 0.0001, 0.9, 0.0001);


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
  // return sine.getSample() * env->process();
  return amplitude * filter->lowPass(sine.getSample()) * env->process();
}

void FmSynth::tick() {
  sine2.tick();
  sine.tick();
  updateFrequency();
}

void FmSynth::setADSR(int newState)
{
  state = newState;

  if (state > 0){
    if(!ADSRset){
    env->gate(true);
    env2->gate(true);
    ADSRset = true;
    }
  }
  else {
    if(ADSRset){
    env->gate(false);
    env2->gate(false);
    ADSRset = false;
    }
  }
}

void FmSynth::setUserInput()
{
  std::string line;
  std::string word;

  while( getInput ){
  std::getline(std::cin, line);
  std::stringstream ss(line);

  std::vector<std::string> vec;

    while (getline(ss, word, ' ')) {
      vec.emplace_back(word);
    }
  if (vec[0] == "fm")
  {
    // std::cout << vec[0] << vec[1] << vec[2] << std::endl;
    try {
     float r = std::stof(vec[1]);
     ratio =  r;
     float d = std::stof(vec[2]);
     modDepth = d;
      }
    catch (const std::exception& e) { // reference to the base of a polymorphic object
       // std::cout << e.what() << std::endl; // information from length_error printed
       std::cout << "wrong input" << std::endl;
     }
    }

    if(vec[0] == "env" || vec[0] == "env2" ){
      try {

        std::string envelopeN = vec[0];
        float sustain = std::stof(vec[3]);

        if(sustain < 0 || sustain > 1) {
          sustain = 0.9;
          std::cout << "sustain level to high or low, choose number between 0 and 1" << std::endl;
        }
         float attack = std::stof(vec[1]);
         float decay = std::stof(vec[2]);
         // float sustain = std::stof(vec[3]);
         float release = std::stof(vec[4]);

         setAdsrValue(envelopeN, attack, decay, sustain, release);

       }
      catch (const std::exception& e) { // reference to the base of a polymorphic object
         // std::cout << e.what() << std::endl; // information from length_error printed
         std::cout << "wrong input" << std::endl;
       }
    }
   if (vec[0] == "q"){
     std::cout << "quit" << std::endl;
     running = false;
     getInput = false;
   }
    // vec.clear();
  }
}

void FmSynth::setAdsrValue(std::string newEnvelopeN, float newAttackRate, float newDecayRate, float newSustainLevel, float newReleaseRate)
  {
    envelopeNumber = newEnvelopeN;
    attackRate = newAttackRate * samplerate;
    decayRate = newDecayRate * samplerate;
    sustainLevel = newSustainLevel;
    releaseRate = newReleaseRate * samplerate;
    if (envelopeNumber == "env"){
    std::cout << "env1" << std::endl;
    env->setADSRrate(attackRate, decayRate, sustainLevel, releaseRate);
  } else {
    std::cout << "env2" << std::endl;
    env2->setADSRrate(attackRate, decayRate, sustainLevel, releaseRate);
    }

  }

int FmSynth::getRunningStatus()
{
  return running;
}
/*---------------- PRIVATE METHODS ----------------*/
//set the synth's frequency
void FmSynth::updateFrequency() {
  sine2.setFrequency((double)frequency * ratio);
  // sine.setFrequency((double)frequency);
  sine.setFrequency((double)frequency + ((sine2.getSample() * env2->process())* (modDepth * frequency * ratio)));
}
