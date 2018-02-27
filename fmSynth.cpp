#include "fmSynth.h"

/*---------------- CONSTRUCTORS / DESTRUCTOR ----------------*/
//constructor - calls the other constructor with midiPitch = 0
FmSynth::FmSynth(float samplerate)
  : FmSynth(samplerate, 0) {}

//using 0 as init value for midiPitch and sine frequency value
FmSynth::FmSynth(float samplerate, float midiPitch)
  : Synth(samplerate), sineCarrier(samplerate, 0), sineModulator(samplerate, 0) {

    setMidiPitch(midiPitch);

    envelopeCarrier.setADSRrate(0.001, 0.0001, 0.9, 0.0001);
    envelopeModulator.setADSRrate(0.001, 0.0001, 0.9, 0.0001);


  }

//destructor - delete s object, set pointer to nullptr
FmSynth::~FmSynth()
{

}

/*---------------- PUBLIC METHODS ----------------*/
//returns the current sample
double FmSynth::getSample() {
  // return sine.getSample() * env->process();
  return amplitude * filter->lowPass(sineCarrier.getSample()) * envelopeCarrier.process();
}

void FmSynth::tick() {
  sineModulator.tick();
  sineCarrier.tick();
  updateFrequency();
}

void FmSynth::setADSRgate(int newState)
{
  state = newState;

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

void FmSynth::setUserInput()
{
  std::string line;
  std::string word;

  while( getInput ){
  std::getline(std::cin, line);
  std::stringstream ss(line);

  std::vector<std::string> userInput;

    while (getline(ss, word, ' ')) {
      userInput.emplace_back(word);
    }
  if (userInput[0] == "fm")
  {
    // std::cout << userInput[0] << userInput[1] << userInput[2] << std::endl;
    try {
     float r = std::stof(userInput[1]);
     ratio =  r;
     float d = std::stof(userInput[2]);
     modDepth = d;
      }
    catch (const std::exception& e) { // reference to the base of a polymorphic object
       // std::cout << e.what() << std::endl; // information from length_error printed
       std::cout << "wrong input" << std::endl;
     }
    }

    if(userInput[0] == "env" || userInput[0] == "env2" ){
      try {

        std::string envelopeN = userInput[0];
        float sustain = std::stof(userInput[3]);

        if(sustain < 0 || sustain > 1) {
          sustain = 0.9;
          std::cout << "sustain level to high or low, choose number between 0 and 1" << std::endl;
        }
         float attack = std::stof(userInput[1]);
         float decay = std::stof(userInput[2]);
         // float sustain = std::stof(userInput[3]);
         float release = std::stof(userInput[4]);

         setAdsrValue(envelopeN, attack, decay, sustain, release);

       }
      catch (const std::exception& e) { // reference to the base of a polymorphic object
         // std::cout << e.what() << std::endl; // information from length_error printed
         std::cout << "wrong input" << std::endl;
       }
    }
   if (userInput[0] == "q"){
     std::cout << "quit" << std::endl;
     running = false;
     getInput = false;
   }
    // userInput.clear();
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
    envelopeCarrier.setADSRrate(attackRate, decayRate, sustainLevel, releaseRate);
  } else {
    std::cout << "env2" << std::endl;
    envelopeModulator.setADSRrate(attackRate, decayRate, sustainLevel, releaseRate);
    }
  }

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
