#ifndef vector3_h
#define vector3_h

struct vector3{
  int x,y,z;

  vector3(int x, int y, int z);

  //Binary Arithmetic Operators
  vector3 operator+(const vector3& v);
  vector3 operator-(const vector3& v);
  vector3 operator*(const vector3& v);
  vector3 operator/(const vector3& v);
  vector3 operator%(const vector3& v);

  //Assignment Operators
  vector3& operator+=(const vector3& v);
  vector3& operator-=(const vector3& v);
  vector3& operator*=(const vector3& v);
  vector3& operator/=(const vector3& v);
  vector3& operator%=(const vector3& v);

  //Unary Arithmetic Operators
  vector3& operator++();    //Prefix
  vector3 operator++(int);  //Postfix
  vector3& operator--();    //Prefix
  vector3 operator--(int);  //Postfix

  void print();
};

#endif