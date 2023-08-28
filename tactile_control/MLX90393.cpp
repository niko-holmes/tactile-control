#include "Arduino.h"
#include "MLX90393.h"
#include "vector3.h"

MLX90393::MLX90393(byte address){
  this->address = address;
  init();
}

void MLX90393::init(){
  //Initiate I2C communication and send RESET command to sensor
  Wire.beginTransmission(address);
  Wire.write(0xF0); //RT command
  Wire.endTransmission();
  
  //Request status byte from sensor
  Wire.requestFrom(address, byte(1));

  if(Wire.available() == 1){
    byte status_byte = Wire.read();
    //Serial.print("Status Byte: ");
    //print8bitBinary(status_byte);
  }
}

void MLX90393::calibrate(){
  /*Calibrate the sensor by taking the first measured XYZ values
  as the XYZ offsets.

  :return: None
  */
  byte readings[7];

  //Start sensor in single measurment mode by sending SM command.
  //Measure in all axes, XYZ.
  Wire.beginTransmission(address);
  Wire.write(0x3E); //SMxyz command
  Wire.endTransmission();

  Wire.requestFrom(address, byte(1));

  if(Wire.available() == 1){
    byte status_byte = Wire.read();
  }

  delay(100);

  //Send read measurement command to sensor. Measure all axes XYZ
  Wire.beginTransmission(address);
  Wire.write(0x4E); //RMxyz command
  Wire.endTransmission();

  //7 bytes: status, xMSB, xLSB, yMSB, yLSB, zMSB, zLSB
  Wire.requestFrom(address, byte(7));

  //Read all 7 bytes of data. Bytes 1 to 7 are measurement data  
  if(Wire.available() == 7){
    for(int i = 0;  i < 7; i++){
      readings[i] = Wire.read();
    }
  }

  //Combine MSB and LSB bytes for each axis reading.
  xOffset = int((readings[1]<<8)|readings[2]);
  yOffset = int((readings[3]<<8)|readings[4]);
  zOffset = int((readings[5]<<8)|readings[6]);
}

vector3 MLX90393::read(){
  /*Read sensor data. Must be called after calibrate() for accurate measurements.

  :return: vector of measured data in X,Y,Z axes.
  */
  byte readings[7];
  vector3 data;

  Wire.beginTransmission(address);
  Wire.write(0x3E); //SMxyz command
  Wire.endTransmission();

  Wire.requestFrom(address, byte(1));

  if(Wire.available() == 1){
    byte status_byte = Wire.read();
  }

  delay(100);

  Wire.beginTransmission(address);
  Wire.write(0x4E); //RMxyz command
  Wire.endTransmission();

  //7 bytes: status, xMSB, xLSB, yMSB, yLSB, zMSB, zLSB
  Wire.requestFrom(address, byte(7));
    
  if(Wire.available() == 7){
    for(int i = 0;  i < 7; i++){
      readings[i] = Wire.read();
    }
  }

  data.x = ((readings[1]<<8)|readings[2]) - xOffset;
  data.y = ((readings[3]<<8)|readings[4]) - yOffset;
  data.z = ((readings[5]<<8)|readings[6]) - zOffset;

  return data; 
}
