#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include "flange.h"

using std::cout;
using std::endl;

#define SR 44100
#define PHASE M_PI / 2

// should be initialized at max delay (min + depth)
FlangeEffect::FlangeEffect(int inDelay)
{
  delayBuf = new DelayLine(inDelay);
  maxDelay = inDelay;
  currTimeIndex = 0;
}

FlangeEffect::~FlangeEffect()
{
  delete delayBuf;
}

// instantaneous delay (ms)
void FlangeEffect::setDelay(double newDelay)
{
  (*delayBuf).setDelayLineDelay(newDelay);
}

// floor of instantaneous delay (ms)
void FlangeEffect::setMinDelay(double newMinDelay)
{
  minDelay = newMinDelay;
}

void FlangeEffect::setWetGain(double newGain)
{
  wetGain = newGain;
}

void FlangeEffect::setDryGain(double newGain)
{
  dryGain = newGain;
}

void FlangeEffect::setFeedbackGain(double newGain)
{
  feedbackGain = newGain;
}

// converts Hz to radian frequency
void FlangeEffect::setRate(double newRate)
{
  delayRate = newRate * 2 * M_PI;
}

// ... (ms)
void FlangeEffect::setDepth(double newDepth)
{
  delayDepth = newDepth;
}

// returns a value >= 0
double FlangeEffect::sineGenerator(){
  // shifts the sine wave above x-axis & scales the amplitude
  double sineWave = (sin (delayRate*currTimeIndex/SR + PHASE) + 1) * (delayDepth / 2);
  double delay = sineWave + minDelay;
  // printf("my delay: %f\n", delay);
  return delay;
}

double FlangeEffect::tick(double input)
{
  // combines dry and effects lines
  double delay = input + (*delayBuf).getCurrentOut() * feedbackGain;
  double output = input * dryGain + (*delayBuf).tick(delay) * wetGain;

  if (output > 1.0)
    output = 1.0;
  else if (output < -1.0)
    output = -1.0;

  // instantaneous delay time is set based on delay rate at current tick
  setDelay(sineGenerator() * SR / 1000.0);
  currTimeIndex++;

  return output;
}
