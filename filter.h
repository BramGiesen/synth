#ifndef _H_FILTER_
#define _H_FILTER_

#include <string>

class Filter
{
public:
  Filter();
  Filter(std::string filterType);
  ~Filter();
  void setFilterState(int state);
  void setFilterType(std::string filterType);
  double lowHighPass(double input);

private:
  int state;
  double output;
  double z;

  bool filterState = 0;

  std::string filterType;
};

#endif //_H_FILTER_
