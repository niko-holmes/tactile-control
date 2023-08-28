#ifndef ServoBD_h
#define ServoBD_h

//#include <stdint.h>
#include "Arduino.h"

class ServoBD{
  private:
    byte pin_f;         //Pin which sends forward signal to servo. Must be PWM pin (3,5,6,9,10,11 in Arduino UNO)
    byte pin_b;         //Pin which sends back signal to servo. Must be PWM pin (3,5,6,9,10,11 in Arduino UNO)

  public:
    ServoBD(byte pin_f, byte pin_b);
    void init();
    void off();
    void forward(uint8_t duty_cycle);
    void backward(uint8_t duty_cycle);
};

#endif