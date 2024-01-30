#ifndef PID_h
#define PID_h

#include "math.h"
#include "Arduino.h"

class PID{
  private:
    int Kp, Ki, Kd;
    unsigned long startTime;
    double cumulativeError;
    double errorRate;
    double lastError;
  
  public:
    PID(int Kp, int Ki, int Kd);
    int calculate(double target, double output);
};

#endif
