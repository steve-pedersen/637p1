#ifndef MAKESINE_H
#define MAKESINE_H

class MakeSine {
 public:
  MakeSine();              // constructor with default frequency and phase
  MakeSine(double, double, int);// constructor that sets frequency, phase and duration
  ~MakeSine();             // destructor
  void setMakeSineFreq(double); // set current frequency of sinusoid
  double getMakeSineFreq();     // get current frequency of sinusoid
  void setMakeSineInitPhase(double); // set initial phase of sinusoid
  double getMakeSineInitPhase();     // get initial phase of sinusoid
  void setMakeSineDuration(int); // set duration of sinusoid
  double getMakeSineDuration();     // get duration of sinusoid
  double getCurrentOut();
  double tick();            // tick method; return next sample from generator

 private:
  long currTimeIndex;  // internal time index n; initialized to 0
  double frequency;    // current frequency
  double initialPhase; // initial phase phi
  double duration;
  double *buffer;
};

#endif
