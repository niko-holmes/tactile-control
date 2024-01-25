#include "Arduino.h"
#include "PID.h"

PID::PID(int Kp, int Ki, int Kd){
  this->Kp = Kp;
  this->Ki = Ki;
  this->Kd = Kd;

  init();
}

void PID::init(){
  startTime = millis();
  lastError = 0;
  cumulativeError = 0;
  errorRate = 0;
}

int PID::calculate(double target, double output){
  /*Calculate plant input u(t). Calculate the error, error integral, and error derivative given the target and measured sensor output.

  :param target:  Target controller is trying to reach
  :param output:  Measured output from sensors
  :returns:  Control variable u(t) as an int
  */
  double elapsedTime = (millis() - startTime) / 1000.00;
  double error = target - output;

  cumulativeError += error * elapsedTime;
  errorRate = (error - lastError) / elapsedTime;
  lastError = error;

  return round((Kp * error) + (Ki * cumulativeError) + (Kd * errorRate));
}
