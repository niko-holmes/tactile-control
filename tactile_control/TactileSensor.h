#ifndef TactileSensor_h
#define TactileSensor_h

#include "Arduino.h"
#include "MLX90393.h"
#include "vector3.h"

class TactileSensor{
  private:
    byte addresses[4];
    MLX90393 sensors[4] = {MLX90393(addresses[0]), MLX90393(addresses[1]), MLX90393(addresses[2]), MLX90393(addresses[3])};
  
  public:
    TactileSensor(byte sensor_address1, byte sensor_address2, byte sensor_address3, byte sensor_address4);
    void init();
    vector3_double readData();
};

#endif