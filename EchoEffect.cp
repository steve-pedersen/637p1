#include <iostream>
#include "echoef.h"

using std::cout;
using std::endl;

EchoEffect::EchoEffect(int inDelay)
{
  delayBuf = new DelayLine(inDelay);
}

EchoEffect::~EchoEffect()
{
  delete delayBuf;
}

void EchoEffect::setDelay(double newDelay)
{
  (*delayBuf).setDelayLineDelay(newDelay);
}

double EchoEffect::getDelay()
{
  return (*delayBuf).getDelayLineDelay();
}

void EchoEffect::setWetGain(double newGain)
{
  wetGain = newGain;
}

double EchoEffect::getWetGain()
{
  return wetGain;
}

void EchoEffect::setDryGain(double newGain)
{
  dryGain = newGain;
}

double EchoEffect::getDryGain()
{
  return dryGain;
}

void EchoEffect::setFeedbackGain(double newGain)
{
  feedbackGain = newGain;
}

double EchoEffect::getFeedbackGain()
{
  return feedbackGain;
}


double EchoEffect::tick(double input)
{
  double temp = (*delayBuf).getCurrentOut() * feedbackGain;
  double output = input * dryGain + (*delayBuf).tick(input + temp) * wetGain;
  return output;
}
