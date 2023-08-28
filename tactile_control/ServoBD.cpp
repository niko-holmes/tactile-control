#include "Arduino.h"
#include "ServoBD.h"

ServoBD::ServoBD(int rpm, byte pin_f, byte pin_b){
  this->pin_f = pin_f;
  this->pin_b = pin_b;
  init();
}

void ServoBD::init(){
  pinMode(pin_f, OUTPUT);
  pinMode(pin_b, OUTPUT);
  off();
}

void ServoBD::off(){
  /*Turns the servo off by setting both forward and back signals to 0.

  :return: None
  */
  analogWrite(pin_f, 0);
  analogWrite(pin_b, 0);
}

void ServoBD::forward(uint8_t duty_cycle){
  /*Set servo to forward rotation until stopped.

  :duty_cycle:  Duty cycle of servo signal. Value between 0 and 255
  :return    :  None
  */

  analogWrite(pin_b, 0);
  analogWrite(pin_f, duty_cycle);
}

void ServoBD::backward(uint8_t duty_cycle){
  /*Set servo to backward rotation until stopped.

  :duty_cycle:  Duty cycle of servo signal. Value between 0 and 255
  :return    :  None
  */

  analogWrite(pin_f, 0);
  analogWrite(pin_b, duty_cycle);
}
