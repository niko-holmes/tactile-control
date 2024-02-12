#ifndef MLX90393_h
#define MLX90393_h

#include <Wire.h>
#include <Arduino.h>
#include "Vector3.h"

class MLX90393{
  private:
    byte m_address;
    Vector3<long> m_zero_offset;
  
  public:
    MLX90393(byte t_address);
    void init();
    Vector3<long> read();
    void calibrate(int t_number_of_samples);
    void reset();
    void print();
};

#endif