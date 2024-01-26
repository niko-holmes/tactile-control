#include "vector3.h"
#include "Arduino.h"

vector3::vector3(int x, int y, int z){
  this->x = x;
  this->y = y;
  this->z = z;
}

//Binary Arithmetic Operators
vector3 vector3::operator+(const vector3& v){
  return vector3(x + v.x, y + v.y, z + v.z);
}
vector3 vector3::operator-(const vector3& v){
  return vector3(x - v.x, y - v.y, z - v.z);
}
vector3 vector3::operator*(const vector3& v){
  return vector3(x * v.x, y * v.y, z * v.z);
}
vector3 vector3::operator/(const vector3& v){
  return vector3(x / v.x, y / v.y, z / v.z);
}
vector3 vector3::operator%(const vector3& v){
  return vector3(x % v.x, y % v.y, z % v.z);
}

//Assignment Operators
vector3& vector3::operator+=(const vector3& v){
  x += v.x;
  y += v.y;
  z += v.z;
  return *this;
}
vector3& vector3::operator-=(const vector3& v){
  x -= v.x;
  y -= v.y;
  z -= v.z;
  return *this;
}
vector3& vector3::operator*=(const vector3& v){
  x *= v.x;
  y *= v.y;
  z *= v.z;
  return *this;
}
vector3& vector3::operator/=(const vector3& v){
  x /= v.x;
  y /= v.y;
  z /= v.z;
  return *this;
}
vector3& vector3::operator%=(const vector3& v){
  x %= v.x;
  y %= v.y;
  z %= v.z;
  return *this;
}

//Unary Arithmetic Operators
vector3& vector3::operator++(){
  ++x;
  ++y;
  ++z;
  return *this;
}
vector3 vector3::operator++(int){
  vector3 temp = *this;
  ++x;
  ++y;
  ++z;
  return temp;
}
vector3& vector3::operator--(){
  --x;
  --y;
  --z;
  return *this;
}
vector3 vector3::operator--(int){
  vector3 temp = *this;
  --x;
  --y;
  --z;
  return temp;
}

void vector3::print(){
  Serial.println("[" + String(x) + ", " + String(y) + ", " + String(z) + "]");
}