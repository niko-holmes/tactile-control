#ifndef PID_h
#define PID_h

#include <Arduino.h>

class PID{
  private:
    int m_kp, m_ki, m_kd;
    unsigned long m_start_time;
    double m_cumulative_error;
    double m_error_rate;
    double m_last_error;
  
  public:
    PID(int t_kp, int t_ki, int t_kd);
    int calculate(double t_target, double t_output);
};

#endif
