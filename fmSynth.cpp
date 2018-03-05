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

    coutInstructions();

  }

//destructor - delete s object, set pointer to nullptr
FmSynth::~FmSynth()
{

}

/*---------------- PUBLIC METHODS ----------------*/
/*returns the current sample and in this function all the process functions are combined */
double FmSynth::getSample()
{
  return amplitude * filter->lowHighPass(sineCarrier.getSample()) * envelopeCarrier.process();
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
    gate = 1;
    ADSRset = true;
    }
  }
  else {
    if(ADSRset){
    gate = 0;
    ADSRset = false;
    }
  }
  envelopeCarrier.gate(gate);
  envelopeModulator.gate(gate);
}



/* function that changes the Attack, Decay, Sustain and Release values of the ADSR envelope */
void FmSynth::setAdsrValue(std::string envelopeNumber, float newAttackRate, float newDecayRate, float sustainLevel, float newReleaseRate)
  {
    this->envelopeNumber = envelopeNumber;
    attackRate = newAttackRate * samplerate;
    decayRate = newDecayRate * samplerate;
    this->sustainLevel = sustainLevel;
    releaseRate = newReleaseRate * samplerate;
    if (envelopeNumber == "envCar"){
    std::cout << "env1" << std::endl;
    envelopeCarrier.setADSRrate(attackRate, decayRate, sustainLevel, releaseRate);
  } else {
    std::cout << "envMod" << std::endl;
    envelopeModulator.setADSRrate(attackRate, decayRate, sustainLevel, releaseRate);
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

//function that handles all user input to change the settings of the FM synth
void FmSynth::setUserInput()
{
  //TODO place function in the MIDI_client or split into a set and a userInput function

  while( getInput ){

    std::getline(std::cin, line);
    if(line == "\0"){//if there is no input, just a enter key

      std::cout << "no input, please enter again" << std::endl;}

      else {//do something with the user input

        std::stringstream ss(line);

        std::vector<std::string> userInput;

        try {

          while (getline(ss, word, ' ')) {
            userInput.emplace_back(word);
          }
          //change fm settings, ratio and modDepth
          if (userInput[0] == "fm"){
            float r = std::stof(userInput[1]);
            ratio =  r;
            float d = std::stof(userInput[2]);
            modDepth = d;
          }// change ADSR settings
          if(userInput[0] == "envCar" || userInput[0] == "envMod" ){
            std::string envelopeN = userInput[0];
            float sustain = std::stof(userInput[3]);

            if(sustain < 0 || sustain > 1) {//limit sustain volume to prevent clipping
              sustain = 0.9;
              std::cout << "sustain level to high or low, choose number between 0 and 1" << std::endl;
            }
            float attack = std::stof(userInput[1]);
            float decay = std::stof(userInput[2]);
            // float sustain = std::stof(userInput[3]);
            float release = std::stof(userInput[4]);

            setAdsrValue(envelopeN, attack, decay, sustain, release);

          }
          if(userInput[0] == "setFilter" ){//change filter settings
            std::string filterType = userInput[1];
            filter->setFilterType(filterType);
          }

          if(userInput[0] == "filterOn" || "filterOff" ){
            int onOff = (userInput[0] == "filterOn") ? 1 : 0;
            filter->setFilterState(onOff);
          }
        }
        catch (const std::exception& e) { // reference to the base of a polymorphic object
          std::cout << "wrong input" << std::endl;
        }

        if (userInput[0] == "q"){
          std::cout << "quit" << std::endl;
          running = false;
          getInput = false;
        }
        if (userInput[0] == " "){
          std::cout << "no input" << std::endl;
        }
        if (userInput[0] == "help"){
          std::cout << "komt morgen" << std::endl;
//           std::cout << " 'q' = quit \n'fm ratio mod' = type fm plus a number for Ratio and a number for modDepth
// 'filterOn' = filter on, at start up the filter is set to a lowPas-filter \n
// 'filterOff' = bypass filter
// 'setFilter' = enter 'setFilter' + lowPass or highPass
// 'envCar a d s r' = set ADSR by typing env followed by number values for attack, decay, sustain and release\n
// 'envMod a d s r' = works the same but this changes the envelope of the modulator" << std::endl;
        }
      }
    }
  }


  void FmSynth::coutInstructions()
  {
    std::cout << "type 'help' for commands" << std::endl;
  }
