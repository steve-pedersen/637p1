#ifndef ECHOEF_H
#define ECHOEF_H

#include "delayef.h"

class EchoEffect : public DelayEffect {
 public:
  EchoEffect(int inDelay = 1024);
  ~EchoEffect();
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
  double dryGain;
  double wetGain;
  double feedbackGain;
};

#endif
