#ifndef _H_FILTER_
#define _H_FILTER_

class Filter
{
public:
  Filter();
  ~Filter();
  double lowPass(double x);
  double highPass(double x);
private:
  double x;
};

#endif //_H_FILTER_
