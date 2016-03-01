#ifndef ECHOEF_H
#define ECHOEF_H

class EchoEffect {
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
