#ifndef ServoBD_h
#define ServoBD_h

#include "Arduino.h"

class ServoBD{
  private:
    byte pinF;         //Pin which sends forward signal to servo. Must be PWM pin (3,5,6,9,10,11 in Arduino UNO)
    byte pinB;         //Pin which sends back signal to servo. Must be PWM pin (3,5,6,9,10,11 in Arduino UNO)

  public:
    ServoBD(byte pinF, byte pinB);
    void pwm(int dutyCycle);
};

#endif
