#include "MLX90393.h"
#include <HardwareSerial.h>


#define SMXYZ 0x3E
#define RMXYZ 0x4E
#define EX 0x80
#define RT 0xF0

MLX90393::MLX90393(byte t_address){
  m_address = t_address;
}

void MLX90393::init(){
  m_zero_offset *= 0;
}

Vector3<long> MLX90393::read(){
  /*Read sensor data. Must be called after calibrate() for accurate measurements.

  :return: vector of measured data in X,Y,Z axes.
  */
  byte readings[7];

  Wire.beginTransmission(m_address);
  Wire.write(SMXYZ); //SMxyz command
  int reply_bit = Wire.endTransmission();

  if(reply_bit != 0){
    Serial.print("Read SMxyz Transmission Failed, error: ");
    Serial.println(reply_bit);
  }

  Wire.requestFrom(m_address, byte(1));

  if(Wire.available() == 1){
    byte status_byte = Wire.read();

    //Check for error bit in status byte
    if(status_byte & 0b00010000){
      Serial.print("Error in measure SMxyz");
    }
  }

  delay(15);

  Wire.beginTransmission(m_address);
  Wire.write(RMXYZ); //RMxyz command
  reply_bit = Wire.endTransmission();

  if(reply_bit != 0){
    Serial.print("Read RMxyz Transmission Failed, error: ");
    Serial.println(reply_bit);
  }

  //7 bytes: status, xMSB, xLSB, yMSB, yLSB, zMSB, zLSB
  Wire.requestFrom(m_address, byte(7));
    
  if(Wire.available() == 7){
    for(int i = 0;  i < 7; i++){
      readings[i] = Wire.read();
    }
  }

  //Check for error bit in status byte
  if(readings[0] & 0b00010000){
    Serial.print("Error in measure RMxyz");
  }

  Vector3<long> data(((readings[1]<<8)|readings[2]),
                     ((readings[3]<<8)|readings[4]),
                     ((readings[5]<<8)|readings[6]));

  return data - m_zero_offset; 
}

void MLX90393::calibrate(int t_number_of_samples){
  /*Calibrate the sensor by taking the average of the first nSamples measured
  as the XYZ offsets.

  :param t_number_of_samples: Number of samples taken to find zero offset
  :return  : None
  */
  init();
  Vector3<long> new_offset;
  
  for(int i = 0; i < t_number_of_samples; i++){
    Vector3<long> data = read();
    new_offset += data;
  }
  
  m_zero_offset = (new_offset / t_number_of_samples);
}

void MLX90393::reset(){
  /*Resets the sensor by sending exit (EX) command followed by reset (RT) command.
  
  :return: None
  */
  //Initiate I2C communication and send EXIT then RESET command to sensor
  Wire.beginTransmission(m_address);
  Wire.write(EX); //EX command
  int reply_bit = Wire.endTransmission();
  if(reply_bit != 0){
    Serial.print("EX Transmission Failed, error: ");
    Serial.println(reply_bit);
  }

  delay(1);
  
  Wire.beginTransmission(m_address);
  Wire.write(RT); //RT command
  reply_bit = Wire.endTransmission();
  
  if(reply_bit != 0){
    Serial.print("RT Transmission Failed, error: ");
    Serial.println(reply_bit);
  }

  //Request status byte from sensor
  Wire.requestFrom(m_address, byte(1));

  if(Wire.available() == 1){
    byte status_byte = Wire.read();
    //Check for error bit in status byte
    if(status_byte & 0b00010000){
      Serial.print("Error in RT");
    }
  }

  delay(2);
}

void MLX90393::print(){
  Serial.println("Adr: " + String(m_address, BIN));
  Serial.print("Offsets: " + m_zero_offset.str());
}
