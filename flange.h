#ifndef FLANGE_H
#define FLANGE_H

#include "echoef.h"
#include "makesine.h"

class FlangeEffect : public EchoEffect {
 public:
  FlangeEffect(int inDelay = 1024);
  ~FlangeEffect();
  void setDelay(double);
  // double getDelay();
  void setWetGain(double);
  // double getWetGain();
  void setDryGain(double);
  // double getDryGain();
  void setFeedbackGain(double);
  // double getFeedbackGain();
  void setRate(double);
  // double getRate();
  void setDepth(double);
  // double getDepth();
  void setMinDelay(double);
  // double getMinDelay();  
  double sineGenerator();
  double tick(double);

 private:
  DelayLine *delayBuf;
  long currTimeIndex;
  double wetGain;
  double dryGain;
  double feedbackGain;
  double delayRate;
  double delayDepth;
  double minDelay;
  double maxDelay;
};

#endif
