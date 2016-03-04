#include <iostream>
#include "delayef.h"

using std::cout;
using std::endl;

DelayEffect::DelayEffect(int inDelay)
{
  delayBuf = new DelayLine(inDelay);
}

DelayEffect::~DelayEffect()
{
  delete delayBuf;
}

void DelayEffect::setDelay(double newDelay)
{
  (*delayBuf).setDelayLineDelay(newDelay);
}

double DelayEffect::getDelay()
{
  return (*delayBuf).getDelayLineDelay();
}

void DelayEffect::setWetGain(double newGain)
{
  wetGain = newGain;
}

double DelayEffect::getWetGain()
{
  return wetGain;
}

void DelayEffect::setDryGain(double newGain)
{
  dryGain = newGain;
}

double DelayEffect::getDryGain()
{
  return dryGain;
}


double DelayEffect::tick(double input)
{
  return input * dryGain + (*delayBuf).tick(input) * wetGain;
}
