#include "TactileSensor.h"
#include <HardwareSerial.h>

TactileSensor::TactileSensor(byte t_multiplexer_pin){
  m_multiplexer_pin = t_multiplexer_pin;
}

void TactileSensor::init(){  
  for(int i = 0; i < 4; i++){
    sensors[i].init();
  }
}

void TactileSensor::calibrate(int t_number_of_samples){
  /*Call calibrate method in all 4 MLX90393 chips.

  :param t_number_of_samples: Number of samples to be taken when calculating zero offset
  :return: None
  */
  Serial.print("Calibrated sensor chips: ");
  for(int i = 0; i < 4; i++){
    sensors[i].init();
    sensors[i].calibrate(t_number_of_samples);
    Serial.print(" ");
    Serial.print(i+1);
  }
  Serial.println();
}

Vector3<long> TactileSensor::readData(){
  /*Read measurement data of the 4 attached MLX90393 chips.
  Calculate data average for X, Y, and Z measurements.
  Return averaged data vector.

  :return: averaged data vector
  */
  Vector3<long> reading_avg;

  for(int i = 0; i < 4; i++){
    reading_avg += sensors[i].read();
  }

  return reading_avg / 4;
}

String TactileSensor::str(){
  return "ID:" + String(m_multiplexer_pin);
}