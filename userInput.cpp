#include "userInput.h"


UserInput::UserInput(FmSynth& fm) : fmSynthRef(fm)
{

}

UserInput::~UserInput()
{

}

//function that gets the user input and gives it to processInput()
void UserInput::getUserInput()
{
  while( getInput ){
    std::getline(std::cin, inputLine);
    processInput(inputLine);
  }
}

/* processes the user input that is given by getUserInput(), it splits the string by every space,
and puts it in a vector as 'words'. first element of the vector stays a string and is used to
determine wich parameters are going to change. the other 'words' are converted to floats if possible. */

void UserInput::processInput(std::string inputLine)
{
      this->inputLine=inputLine;

      if(inputLine == "\0"){//if there is no input, just a enter key

          std::cout << "no input, please enter again" << std::endl;}

      else {//do something with the user input

        std::stringstream ss(inputLine);

        // std::vector<std::string> userInput;

        try {

          while (getline(ss, inputWord, ' ')) {
            userInputVec.emplace_back(inputWord);
          }

          int inputLenght = ((userInputVec.size())-1);
          std::cout << inputLenght << std::endl;

          for (int index = 1; index <= inputLenght; index++)
          {
            parameterVec.push_back(std::stof(userInputVec[index]));
          }


          // change fm settings, ratio and modDepth
          if (userInputVec[0] == "fm"){
            fmSynthRef.ratio =  parameterVec[0];
            fmSynthRef.modDepth = parameterVec[1];
          }// change ADSR settings
          else if(userInputVec[0] == "envCar" || userInputVec[0] == "envMod" ){
              std::string envelopeN = userInputVec[0];
              if(parameterVec[2] < 0 || parameterVec[2] > 1) {//limit sustain volume to prevent clipping
              parameterVec[2] = 0.9;
              std::cout << "sustain level to high or low, choose number between 0 and 1" << std::endl;
            }
              if (envelopeN == "envCar"){
                std::cout << "the envelope of the carrier is set" << std::endl;
                fmSynthRef.envelopeCarrier.setADSRrate(parameterVec[0], parameterVec[1], parameterVec[2], parameterVec[3]);
            } else {
                std::cout << "the envelope of the modulator is set" << std::endl;
                fmSynthRef.envelopeModulator.setADSRrate(parameterVec[0], parameterVec[1], parameterVec[2], parameterVec[3]);
            }
          }

          else if(userInputVec[0] == "setFilter" ){//change filter settings
            std::string filterType = userInputVec[1];
            fmSynthRef.filter->setFilterType(filterType);
          }

          else if(userInputVec[0] == "filterOn" || userInputVec[0] == "filterOff" ){
            int onOff = (userInputVec[0] == "filterOn") ? 1 : 0;
            fmSynthRef.filter->setFilterState(onOff);
          }

          else if(userInputVec[0] == "delayTime"){
            fmSynthRef.delay.setDelayTime(parameterVec[0]);
          }

          else if(userInputVec[0] == "delayOn" ||userInputVec[0] == "delayOff" ){
              int onOff = (userInputVec[0] == "DelayOn") ? 1 : 0;
              fmSynthRef.delay.setDelayState(onOff);
          }


          else if(userInputVec[0] == "delayFeedback"){
              fmSynthRef.delay.setFeedback(parameterVec[2]);
          }
        else if (userInputVec[0] == "q"){
          std::cout << "quit" << std::endl;
          fmSynthRef.running = false;
          getInput = false;
        }
        else if (userInputVec[0] == " "){
          std::cout << "no input" << std::endl;
        }
        else if (userInputVec[0] == "help"){
          std::cout << fmSynthRef.help.test << std::endl;
        }
        else {
          std::cout << "input not recognized" << std::endl;
        }
        userInputVec.clear();
        std::cout << "vec cleared" << std::endl;
        }
        catch (const std::exception& e) { // reference to the base of a polymorphic object
          std::cout << "wrong input" << std::endl;
        }

      }
}
