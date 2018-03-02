#ifndef _H_FILTER_
#define _H_FILTER_

#include <string>

class Filter
{
public:
  Filter(double h0, double h1, std::string filterType);
  Filter();
  ~Filter();
  void setFilterState(int state);
  void setFilterCoef(double h0, double h1);
  void setFilterType(std::string filterType);
  double lowHighPass(double x);
private:
  int state;
  double input;
  double output;
  double h0;
  double h1;
  double z;

  bool filterState = 0;

  std::string filterType;
};

#endif //_H_FILTER_
