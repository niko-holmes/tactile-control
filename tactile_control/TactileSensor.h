#ifndef TactileSensor_h
#define TactileSensor_h

#include "Arduino.h"
#include "MLX90393.h"
#include "vector3.h"

class TactileSensor{
  private:
    byte mplxr_pin;
    MLX90393 sensors[4] = {MLX90393(0b0001100), MLX90393(0b0001101), MLX90393(0b0001110), MLX90393(0b0001111)};

    vector3 offset;

  public:
    TactileSensor(byte mplxr_pin);
    void init();
    vector3_double readData();
};

#endif