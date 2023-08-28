#include "Arduino.h"
#include "PID.h"

PID::PID(int Kp, int Ki, int Kd){
  this->Kp = Kp;
  this->Ki = Ki;
  this->Kd = Kd;

  init();
}

void PID::init(){
  start_time = millis();
  last_error = 0;
  cumulative_error = 0;
  error_rate = 0;
}

int PID::calculate(double target, double output){
  /*Calculate plant input u(t). Calculate the error, error integral, and error derivative given the target and measured sensor output.

  :target:  Target controller is trying to reach
  :output:  Measured output from sensors
  :return:  Control variable u(t) as an int
  */
  double elapsed_time = (millis() - start_time) / 1000.00;
  double error = target - output;

  cumulative_error += error * elapsed_time;
  error_rate = (error - last_error) / elapsed_time;
  last_error = error;

  return round((Kp * error) + (Ki * cumulative_error) + (Kd * error_rate));
}
