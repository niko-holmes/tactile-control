#ifndef ServoBD_h
#define ServoBD_h

#include <Arduino.h>

class ServoBD{
  private:
    byte m_pin_f;         //Pin which sends forward signal to servo. Must be PWM pin (3,5,6,9,10,11 in Arduino UNO)
    byte m_pin_b;         //Pin which sends back signal to servo. Must be PWM pin (3,5,6,9,10,11 in Arduino UNO)

  public:
    ServoBD(byte t_pin_f, byte t_pin_b);
    void pwm(int t_duty_cycle);
};

#endif
