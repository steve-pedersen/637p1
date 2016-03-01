#include <iostream>
#include "makesine.h"
#include <math.h>

// #define M_PI 3.14159265
#define SR 44100

using std::cout;
using std::endl;

MakeSine::MakeSine() 
{
  buffer = new double [1024];
  frequency = 200.0 * 2 * M_PI;
  initialPhase = 0.5 * M_PI;
  currTimeIndex = 0;
  duration = 2000;
}

MakeSine::MakeSine(double newFreq, double newPhase, int newDuration)
{
  buffer = new double [1024];
  frequency = newFreq * 2 * M_PI;
  initialPhase = newPhase * M_PI;
  currTimeIndex = 0;
  duration = newDuration;
}

MakeSine::~MakeSine()
{
  delete [] buffer;
}

void MakeSine::setMakeSineFreq(double newFreq)
{
  frequency = newFreq * 2 * M_PI;
}

double MakeSine::getMakeSineFreq()
{
  return frequency;
}

void MakeSine::setMakeSineInitPhase(double newPhase)
{
  initialPhase = newPhase * M_PI;
}

double MakeSine::getMakeSineInitPhase()
{
  return initialPhase;
}

void MakeSine::setMakeSineDuration(int newDuration)
{
  duration = newDuration;
}

double MakeSine::getMakeSineDuration()
{
  return duration;
}

double MakeSine::getCurrentOut(){
  return sin (frequency*currTimeIndex/SR + initialPhase);
}

double MakeSine::tick()
{
  double output = getCurrentOut();

  if (output > 1.0)
    output = 1.0;
  else if (output < -1.0)
    output = -1.0;

  currTimeIndex++;

  return output;  
}