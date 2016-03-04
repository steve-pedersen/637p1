#ifndef FLANGE_H
#define FLANGE_H

#include "echoef.h"
#include "makesine.h"

class Flange : public EchoEffect {
 public:
  DelayEffect(int inDelay = 1024);
  ~DelayEffect();
  void setDelay(double);
  double getDelay();
  void setWetGain(double);
  double getWetGain();
  void setDryGain(double);
  double getDryGain();
  double tick(double);

 private:
  DelayLine *delayBuf;
  double wetGain;
  double dryGain;
};

#endif
