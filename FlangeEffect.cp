#include <iostream>
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
  double sineWave = sin (delayRate*currTimeIndex/SR + PHASE);

  // shifts the sine wave above x-axis
  return (sineWave + minDelay + delayDepth);
}

double FlangeEffect::tick(double input)
{
  // combines dry and effects lines
  double delay = (*delayBuf).getCurrentOut() * feedbackGain;
  double output = input * dryGain + (*delayBuf).tick(input + delay) * wetGain;

  // instantaneous delay time is set based on delay rate at current tick
  setDelay(sineGenerator());
  currTimeIndex++;

  return output;
}
