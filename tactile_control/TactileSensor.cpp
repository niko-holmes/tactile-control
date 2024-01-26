#include "HardwareSerial.h"
#include "Arduino.h"
#include "TactileSensor.h"
#include "vector3.h"

TactileSensor::TactileSensor(byte mplxrPin){
  this->mplxrPin = mplxrPin;
}

void TactileSensor::init(){  
  for(int i = 0; i < 4; i++){
    sensors[i].init();
  }
}

void TactileSensor::calibrate(int nSamples){
  /*Call calibrate method in all 4 MLX90393 chips.

  :param nSamples: Number of samples to be taken when calculating zero offset
  :returns: None
  */
  Serial.print("Calibrated sensor chips: ");
  for(int i = 0; i < 4; i++){
    sensors[i].init();
    sensors[i].calibrate(nSamples);
    Serial.print(" ");
    Serial.print(i+1);
  }

  Serial.println();
}

vector3<long> TactileSensor::readData(){
  /*Read measurement data of the 4 attached MLX90393 chips.
  Calculate data average for X, Y, and Z measurements.
  Return averaged data vector.

  :returns: averaged data vector
  */
  vector3<long> readingAvg;

  for(int i = 0; i < 4; i++){
    readingAvg += sensors[i].read();
  }

  return readingAvg / 4;
}

String TactileSensor::str(){
  return "ID:" + String(mplxrPin);
}