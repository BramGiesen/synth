#include "filter.h"

Filter::Filter()
{

}

Filter::~Filter()
{

}

double Filter::lowPass(double newX)
{
  x = newX;
  static double xx = 0;
  double y = 0.5 * (x + xx);
  xx = x;
  return y;
}

double Filter::highPass(double newX)
{
  x = newX;
  static double xx = 0;
  double y = 0.5 * (x - xx);
  xx = x;
  return y;
}
