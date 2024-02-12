#include "ServoBD.h"

ServoBD::ServoBD(byte t_pin_f, byte t_pin_b){
  m_pin_f = t_pin_f;
  m_pin_b = t_pin_b;
  pinMode(m_pin_f, OUTPUT);
  pinMode(m_pin_b, OUTPUT);
  pwm(0);
}

void ServoBD::pwm(int t_duty_cycle){
  /*Set servo to rotate at dutyCycle pwm until stopped

  :param t_duty_cycle:  Duty cycle of servo signal. Value between -255 and 255
  :return:  None
  */

  t_duty_cycle = (t_duty_cycle > 255) ? 255 : t_duty_cycle;
  t_duty_cycle = (t_duty_cycle < -255) ? -255 : t_duty_cycle;
  
  if(t_duty_cycle > 0){
    analogWrite(m_pin_b, 0);
    analogWrite(m_pin_f, abs(t_duty_cycle));
  }
  else{
    analogWrite(m_pin_f, 0);
    analogWrite(m_pin_b, abs(t_duty_cycle));
  }
}
