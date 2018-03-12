#include "delay.h"

Delay::Delay()
{

}

Delay::Delay(int delayTime)
{

  this->delayTime=delayTime;

  setDelayTime(delayTime);
}

Delay::Delay(int bufferSize, int delayTime)
{
  // setBufferSize(int bufferSize);
  // setDelayTime(int delay);
}

Delay::~Delay()
{

}

void Delay::setBufferSize(int bufferSize)
{
  this->bufferSize=bufferSize;
}

void Delay::setDelayTime(float delayTime)
{
  this->delayTime=delayTime;

  if(delayTime>bufferSize){
    std::cout << "delaytime is bigger then buffersize, increase buffer or set a shorter delay time" << std::endl;
  } else {
  delayRead = bufferSize - delayTime;
  // std::cout << "delaytime in setDelayTime = " << delayRead << std::endl;
  }
}

void Delay::setDelayState(int OnOff)
{
  this->OnOff=OnOff;
  delayRunning = OnOff;
  std::cout << "delayRunning = " << delayRunning << std::endl;
}

void Delay::setDryWet(int wet)
{
  this->wet=wet;
}

void Delay::setFeedback(float feedback)
{
  this->feedback=feedback;
  std::cout << "feedback = " << feedback << std::endl;
}

double Delay::process(double input)
{
  this->input=input;
  if (delayRunning) {
    input = input + (delayedSignal * feedback);
    delayWrite = delayWrite % bufferSize;
    delayRead = delayRead % bufferSize;
    buffer[delayWrite] = input;
    delayedSignal = buffer[delayRead];
    delayWrite++;
    delayRead++;
  } else {
    delayedSignal = 0;
    // std::cout << "niet aan" << std::endl;
  }
  return input + delayedSignal;
}
