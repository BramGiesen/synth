#include <iostream>
// struct with instructions how to change the settings of the fmSynth
struct helpFile
{
  std::string test = "\n'fm' ratio mod = type fm plus a number for Ratio and a number for modDepth\n"
"'filterOn' = filter on, at start up the filter is set to a lowPas-filter \n"
"'filterOff' = bypass filter\n"
"'setFilter' = enter setFilter + lowPass or highPass\n"
"'envCar' a d s r = set ADSR by typing env followed by number values for attack, decay, sustain and release\n"
"'envMod' a d s r = works the same but this changes the envelope of the modulator";
};
