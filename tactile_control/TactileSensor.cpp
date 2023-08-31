#include "HardwareSerial.h"
#include "Arduino.h"
#include "TactileSensor.h"
#include "vector3.h"

TactileSensor::TactileSensor(byte mplxr_pin){
  this->mplxr_pin = mplxr_pin;
}

void TactileSensor::init(){  
  Serial.print("Calibrating sensor chips: ");
  for(int i = 0; i < 4; i++){
    Serial.print(" ");
    Serial.print(i+1);
    sensors[i].calibrate();
  }

  Serial.println();
}

vector3_double TactileSensor::readData(){
  /*Read measurement data of the 4 attached MLX90393 chips.
  Calculate data average for X, Y, and Z measurements.
  Convert measurement data to force.
  Return force vector.

  :return: measured force vector
  */

  int xReadings[4];
  int yReadings[4];
  int zReadings[4];

  for(int i = 0; i < 4; i++){
    vector3 raw_data = sensors[i].read();

    xReadings[i] = raw_data.x;
    yReadings[i] = raw_data.y;
    zReadings[i] = raw_data.z;

    //ADD DELAY??
  }

  //Average readings of all 4 Hall-effect sensors
  vector3_double reading_avg;
  reading_avg.x = (xReadings[0] + xReadings[1] + xReadings[2] + xReadings[3]) / 4;
  reading_avg.y = (yReadings[0] + yReadings[1] + yReadings[2] + yReadings[3]) / 4;
  reading_avg.z = (zReadings[0] + zReadings[1] + zReadings[2] + zReadings[3]) / 4;

  //Convert sensor data (Tesla) to force (Newtons)
  vector3_double force;
  force.x = -0.5822 * reading_avg.x + 2.252;
  force.y = -0.5822 * reading_avg.y + 2.252;
  force.z = (-0.0006682 * reading_avg.z * reading_avg.z) + (0.1202 * reading_avg.z) - 1.921;

  return force;
}