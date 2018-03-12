#ifndef _H_DELAY_
#define _H_DELAY_

#include <iostream>
#include <unistd.h>
#include <vector>

class Delay
{
public:
  Delay();
  Delay(int delayTime);
  Delay(int bufferSize, int delayTime);
  ~Delay();
void setDelayState(int OnOff);
void setDryWet(int wet);
void setDelayTime(float delayTime);
void setFeedback(float feedback);
void setBufferSize(int bufferSize);
double process(double input);

private:
  bool delayRunning = false;

  int samplerate = 44100;
  int bufferSize = 132300;
  int delayWrite = 0;
  int delayRead;
  int wet;
  int delayTime = 0;
  int OnOff;
  float feedback = 0;

  double buffer[132300];
  double input;
  double output;
  double delayedSignal;

};

#endif // _H_DELAY_
