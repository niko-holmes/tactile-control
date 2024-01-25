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
  Serial.print("Calibrating sensor chips: ");
  for(int i = 0; i < 4; i++){
    Serial.print(" ");
    Serial.print(i+1);
    sensors[i].init();
    sensors[i].calibrate(nSamples);
  }

  Serial.println();
}

vector3Double TactileSensor::readData(){
  /*Read measurement data of the 4 attached MLX90393 chips.
  Calculate data average for X, Y, and Z measurements.
  Return filtered data vector.

  :return: filtered data vector
  */

  int xReadings[4];
  int yReadings[4];
  int zReadings[4];

  for(int i = 0; i < 4; i++){
    vector3 rawData = sensors[i].read();

    xReadings[i] = rawData.x;
    yReadings[i] = rawData.y;
    zReadings[i] = rawData.z;
  }

  //Average readings of all 4 Hall-effect sensors
  vector3Double readingAvg;
  readingAvg.x = (xReadings[0] + xReadings[1] + xReadings[2] + xReadings[3]) / 4.0;
  readingAvg.y = (yReadings[0] + yReadings[1] + yReadings[2] + yReadings[3]) / 4.0;
  readingAvg.z = (zReadings[0] + zReadings[1] + zReadings[2] + zReadings[3]) / 4.0;

  return readingAvg;
}
