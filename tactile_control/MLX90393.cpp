#include "HardwareSerial.h"
#include "Arduino.h"
#include "MLX90393.h"
#include "vector3.h"

MLX90393::MLX90393(byte address){
  this->address = address;
}

void MLX90393::calibrate(){
  /*Calibrate the sensor by taking the average of the first 10 measured XYZ values
  as the XYZ offsets.

  :return: None
  */

  byte readings[7];

  //Start sensor in single measurment mode by sending SM command.
  //Measure in all axes, XYZ.
  Wire.beginTransmission(address);
  Wire.write(0x3E); //SMxyz command
  int c = Wire.endTransmission();

  if(c != 0){
    Serial.print("Cal. SMxyz Transmission Failed, error: ");
    Serial.println(c);
  }

  Wire.requestFrom(address, byte(1));

  if(Wire.available() == 1){
    byte status_byte = Wire.read();

    //Check for error bit in status byte
    if(status_byte & 0b00010000){
      Serial.print("Error in calibration SMxyz");
    }
  }

  delay(100);

  //Send read measurement command to sensor. Measure all axes XYZ
  Wire.beginTransmission(address);
  Wire.write(0x4E); //RMxyz command
  c = Wire.endTransmission();

  if(c != 0){
    Serial.print("Cal. RMxyz Transmission Failed, error: ");
    Serial.println(c);
  }

  //7 bytes: status, xMSB, xLSB, yMSB, yLSB, zMSB, zLSB
  Wire.requestFrom(address, byte(7));

  //Read all 7 bytes of data. Bytes 1 to 7 are measurement data  
  if(Wire.available() == 7){
    for(int i = 0;  i < 7; i++){
      readings[i] = Wire.read();
    }
  }

  //Check for error bit in status byte
  if(readings[0] & 0b00010000){
    Serial.print("Error in calibration RMxyz");
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
  int c = Wire.endTransmission();

  if(c != 0){
    Serial.print("Read SMxyz Transmission Failed, error: ");
    Serial.println(c);
  }

  Wire.requestFrom(address, byte(1));

  if(Wire.available() == 1){
    byte status_byte = Wire.read();

    //Check for error bit in status byte
    if(status_byte & 0b00010000){
      Serial.print("Error in measure SMxyz");
    }
  }

  delay(100);

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
    byte status_byte = Wire.read();
    //Check for error bit in status byte
    if(status_byte & 0b00010000){
      Serial.print("Error in RT");
    }
  }

  delay(2);
}
