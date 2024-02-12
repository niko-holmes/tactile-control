#include "PID.h"

PID::PID(int t_kp, int t_ki, int t_kd){
  m_kp = t_kp;
  m_ki = t_ki;
  m_kd = t_kd;
  m_start_time = millis();
  m_last_error = 0;
  m_cumulative_error = 0;
  m_error_rate = 0;
}

int PID::calculate(double t_target, double t_output){
  /*Calculate plant input u(t). Calculate the error, error integral, and error derivative given the target and measured sensor output.

  :param t_target:  Target controller is trying to reach
  :param t_output:  Measured output from sensors
  :return:  Control variable u(t) as an int
  */
  double elapsed_time = (millis() - m_start_time) / 1000.00;
  double error = t_target - t_output;

  m_cumulative_error += error * elapsed_time;
  m_error_rate = (error - m_last_error) / elapsed_time;
  m_last_error = error;

  return round((m_kp * error) + (m_ki * m_cumulative_error) + (m_kd * m_error_rate));
}
