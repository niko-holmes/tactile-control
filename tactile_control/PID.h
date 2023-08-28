#ifndef PID_h
#define PID_h

#include "math.h"
#include "Arduino.h"

class PID{
  private:
    int Kp, Ki, Kd;

    double cumulative_error;
    double error_rate;

    unsigned long start_time;
    double last_error;
  
  public:
    PID(int Kp, int Ki, int Kd);
    void init();
    int calculate(double target, double output);
};

#endif