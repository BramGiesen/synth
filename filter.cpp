#include "filter.h"
#include <iostream>

Filter::Filter()
{

}

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

void Filter::setFilterState(int state)
{
  this->state=state;
  filterState = state;
}

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
