#ifndef MLX90393_h
#define MLX90393_h

#include "Wire.h"
#include "Arduino.h"
#include "vector3.h"

class MLX90393{
  private:
    byte address;
    vector3<long> zeroOffset;
  
  public:
    MLX90393(byte address);
    void init();
    vector3<long> read();
    void calibrate(int nSamples);
    void reset();
    void print();
};

#endif