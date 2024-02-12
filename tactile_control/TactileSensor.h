#ifndef TactileSensor_h
#define TactileSensor_h

#include <Arduino.h>
#include "MLX90393.h"
#include "Vector3.h"

class TactileSensor{
  private:
    byte m_multiplexer_pin;
    MLX90393 sensors[4] = {MLX90393(0b0001100), 
                           MLX90393(0b0001101),
                           MLX90393(0b0001110),
                           MLX90393(0b0001111)};
  public:
    TactileSensor(byte t_multiplexer_pin);
    void init();
    void calibrate(int t_number_of_samples);
    Vector3<long> readData();
    String str();
};

#endif