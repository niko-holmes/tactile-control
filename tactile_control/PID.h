#ifndef PID_h
#define PID_h

#include "math.h"
#include "Arduino.h"

class PID{
  private:
    int Kp, Ki, Kd;

    double cumulativeError;
    double errorRate;

    unsigned long startTime;
    double lastError;
  
  public:
    PID(int Kp, int Ki, int Kd);
    void init();
    int calculate(double target, double output);
};

#endif
