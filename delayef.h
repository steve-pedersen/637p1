#ifndef DELAYEF_H
#define DELAYEF_H

#include "delayl.h"

class DelayEffect {
 public:
  DelayEffect(int inDelay = 1024);
  ~DelayEffect();
  void setDelay(double);
  double getDelay();
  void setWetGain(double);
  double getWetGain();
  void setDryGain(double);
  double getDryGain();
  void setFeedbackGain(double);
  double getFeedbackGain();
  double tick(double);

 private:
  DelayLine *delayBuf;
  double wetGain;
  double dryGain;
  double feedbackGain;
};

#endif
