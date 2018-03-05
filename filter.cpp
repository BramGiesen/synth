#include "filter.h"
#include <iostream>

Filter::Filter()
{

}
/*constructor of the Filter class, initialize the 2 filter coefficients,
h0 and h1 and sets a filterType; lowPass or highPass */
Filter::Filter(double h0, double h1, std::string filterType)
{
  this->h0=h0;
  this->h1=h1;
  this->filterType=filterType;
  setFilterType(filterType);
}

Filter::~Filter()
{
}

/*sets the filterState if the filterState is 0 the process function returns the input directly*/
void Filter::setFilterState(int state)
{
  this->state=state;
  filterState = state;
}

/*set high- or lowPass filter */
void Filter::setFilterType(std::string filterType)
{
  this->filterType=filterType;
  z = (filterType == "highPass") ? -1 : 1;
}

void Filter::setFilterCoef(double h0, double h1)
{
  this->h0=h0;
  this->h1=h1;
}

/*process function of the filter, takes a input signal and returns the filtered signal.
it can switch between a high- or lowPass filter by multiplying right part with -1 to convert + x[n-1] to - x[n-1]
n = delayed output and x is the input */
double Filter::lowHighPass(double input)
{
  this->input=input;

  if(filterState){
    static double delayedInput = 0;
    output = 0.5 * ((h0*input) + (h1*delayedInput)* z);
    delayedInput = input;
  } else {
    output = input;
  }
  return output;
}
