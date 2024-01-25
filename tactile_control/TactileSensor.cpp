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

vector3Double TactileSensor::readData(){
  /*Read measurement data of the 4 attached MLX90393 chips.
  Calculate data average for X, Y, and Z measurements.
  Return averaged data vector.

  :returns: averaged data vector
  */
  vector3Double readingAvg;

  for(int i = 0; i < 4; i++){
    vector3 rawData = sensors[i].read();

    readingAvg.x += rawData.x;
    readingAvg.y += rawData.y;
    readingAvg.z += rawData.z;
  }

  //Average readings of all 4 Hall-effect sensors
  readingAvg.x /= 4.0;
  readingAvg.y /= 4.0;
  readingAvg.z /= 4.0;

  return readingAvg;
}

String TactileSensor::str(){
  return "ID:" + String(mplxrPin);
}