#include "Arduino.h"
#include "ServoBD.h"

ServoBD::ServoBD(byte pinF, byte pinB){
  this->pin_f = pinF;
  this->pin_b = pinB;
  init();
}

void ServoBD::init(){
  pinMode(pinF, OUTPUT);
  pinMode(pinB, OUTPUT);
  off();
}

void ServoBD::off(){
  /*Turns the servo off by setting both forward and back signals to 0.

  :return: None
  */
  analogWrite(pinF, 0);
  analogWrite(pinB, 0);
}

void ServoBD::forward(uint8_t dutyCycle){
  /*Set servo to forward rotation until stopped.

  :param dutyCycle:  Duty cycle of servo signal. Value between 0 and 255
  :return:  None
  */

  analogWrite(pinB, 0);
  analogWrite(pinF, dutyCycle);
}

void ServoBD::backward(uint8_t dutyCycle){
  /*Set servo to backward rotation until stopped.

  :param dutyCycle:  Duty cycle of servo signal. Value between 0 and 255
  :return    :  None
  */

  analogWrite(pinF, 0);
  analogWrite(pinB, dutyCycle);
}
