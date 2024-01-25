#ifndef MLX90393_h
#define MLX90393_h

#include "Wire.h"
#include "Arduino.h"
#include "vector3.h"

class MLX90393{
  private:
    byte address;
    long int xOffset;
    long int yOffset;
    long int zOffset;
  
  public:
    MLX90393(byte address);
    void init();
    vector3 read();
    void calibrate(int nSamples);
    void reset();
    String str();
};

#endif