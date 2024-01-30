#include "Arduino.h"
#include "ServoBD.h"

ServoBD::ServoBD(byte pinF, byte pinB){
  this->pin_f = pinF;
  this->pin_b = pinB;
  pinMode(pinF, OUTPUT);
  pinMode(pinB, OUTPUT);
  pwm(0);
}

void ServoBD::pwm(int dutyCycle){
  /*Set servo to rotate at dutyCycle pwm until stopped

  :param dutyCycle:  Duty cycle of servo signal. Value between -255 and 255
  :return:  None
  */

  dutyCyle = (dutyCycle > 255) ? 255 : dutyCycle;
  dutyCyle = (dutyCycle < -255) ? -255 : dutyCycle;
  
  if(dutyCycle > 0){
    analogWrite(pinB, 0);
    analogWrite(pinF, abs(dutyCycle));
  }
  else{
    analogWrite(pinF, 0);
    analogWrite(pinB, abs(dutyCycle));
  }
  
  
}
