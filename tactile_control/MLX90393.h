#ifndef MLX90393_h
#define MLX90393_h

#include "Wire.h"
#include "Arduino.h"
#include "vector3.h"

class MLX90393{
  private:
    byte address;
    int xOffset;
    int yOffset;
    int zOffset;
  
  public:
    MLX90393(byte address);
    void calibrate();
    vector3 read();
    void reset();
};

#endif