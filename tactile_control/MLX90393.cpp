#include "HardwareSerial.h"
#include "Arduino.h"
#include "MLX90393.h"
#include "vector3.h"

MLX90393::MLX90393(byte address){
  this->address = address;
}

void MLX90393::init(){
  xOffset = 0;
  yOffset = 0;
  zOffset = 0;
}

vector3 MLX90393::read(){
  /*Read sensor data. Must be called after calibrate() for accurate measurements.

  :return: vector of measured data in X,Y,Z axes.
  */
  byte readings[7];
  vector3 data;

  Wire.beginTransmission(address);
  Wire.write(0x3E); //SMxyz command
  int c = Wire.endTransmission();

  if(c != 0){
    Serial.print("Read SMxyz Transmission Failed, error: ");
    Serial.println(c);
  }

  Wire.requestFrom(address, byte(1));

  if(Wire.available() == 1){
    byte statusByte = Wire.read();

    //Check for error bit in status byte
    if(statusByte & 0b00010000){
      Serial.print("Error in measure SMxyz");
    }
  }

  delay(15);

  Wire.beginTransmission(address);
  Wire.write(0x4E); //RMxyz command
  c = Wire.endTransmission();

  if(c != 0){
    Serial.print("Read RMxyz Transmission Failed, error: ");
    Serial.println(c);
  }

  //7 bytes: status, xMSB, xLSB, yMSB, yLSB, zMSB, zLSB
  Wire.requestFrom(address, byte(7));
    
  if(Wire.available() == 7){
    for(int i = 0;  i < 7; i++){
      readings[i] = Wire.read();
    }
  }

  //Check for error bit in status byte
  if(readings[0] & 0b00010000){
    Serial.print("Error in measure RMxyz");
  }

  data.x = ((readings[1]<<8)|readings[2]) - xOffset;
  data.y = ((readings[3]<<8)|readings[4]) - yOffset;
  data.z = ((readings[5]<<8)|readings[6]) - zOffset;

  return data; 
}

void MLX90393::calibrate(int nSamples){
  /*Calibrate the sensor by taking the average of the first nSamples measured
  as the XYZ offsets.

  :nSamples: Number of samples taken to find zero offset
  :return  : None
  */
  init();
  
  for(int i=0; i < nSamples; i++){
    vector3 data = read();
    xOffset += data.x;
    yOffset += data.y;
    zOffset += data.z;
  }

  xOffset /= nSamples;
  yOffset /= nSamples;
  zOffset /= nSamples;

  }

void MLX90393::reset(){
  /*Resets the sensor by sending exit (EX) command followed by reset (RT) command.
  
  :return: None
  */
  //Initiate I2C communication and send EXIT then RESET command to sensor
  Wire.beginTransmission(address);
  Wire.write(0x80); //EX command
  int c = Wire.endTransmission();
  if(c != 0){
    Serial.print("EX Transmission Failed, error: ");
    Serial.println(c);
  }

  delay(1);
  
  Wire.beginTransmission(address);
  Wire.write(0xF0); //RT command
  c = Wire.endTransmission();
  
  if(c != 0){
    Serial.print("RT Transmission Failed, error: ");
    Serial.println(c);
  }

  //Request status byte from sensor
  Wire.requestFrom(address, byte(1));

  if(Wire.available() == 1){
    byte statusByte = Wire.read();
    //Check for error bit in status byte
    if(statusByte & 0b00010000){
      Serial.print("Error in RT");
    }
  }

  delay(2);
}

String MLX90393::str(){
  return "Adr: " + String(address, BIN) + 
    "\nOffsets: " + String(xOffset) + ", " + String(yOffset) + ", " + String(zOffset);
}
