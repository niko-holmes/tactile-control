#ifndef Vector3_h
#define Vector3_h

template <typename T>
class Vector3
{
  public:
    T x, y, z;

    //Constructors
    Vector3(T t_x = 0, T t_y = 0, T t_z = 0){
      x = t_x;
      y = t_y;
      z = t_z;
    }

    //Binary Arithmetic Operators
    Vector3 operator+(const Vector3& v)       {return Vector3(x + v.x, y + v.y, z + v.z);}
    Vector3 operator+(const int& n)           {return Vector3(x + n, y + n, z + n);}
    Vector3 operator+(const unsigned int& n)  {return Vector3(x + n, y + n, z + n);}
    Vector3 operator+(const long& n)          {return Vector3(x + n, y + n, z + n);}
    Vector3 operator+(const unsigned long& n) {return Vector3(x + n, y + n, z + n);}
    Vector3 operator+(const double& n)        {return Vector3(x + n, y + n, z + n);}

    Vector3 operator-(const Vector3& v){return Vector3(x - v.x, y - v.y, z - v.z);}
    Vector3 operator-(const int& n)           {return Vector3(x - n, y - n, z - n);}
    Vector3 operator-(const unsigned int& n)  {return Vector3(x - n, y - n, z - n);}
    Vector3 operator-(const long& n)          {return Vector3(x - n, y - n, z - n);}
    Vector3 operator-(const unsigned long& n) {return Vector3(x - n, y - n, z - n);}
    Vector3 operator-(const double& n)        {return Vector3(x - n, y - n, z - n);}

    Vector3 operator*(const Vector3& v){return Vector3(x * v.x, y * v.y, z * v.z);}
    Vector3 operator*(const int& n)           {return Vector3(x * n, y * n, z * n);}
    Vector3 operator*(const unsigned int& n)  {return Vector3(x * n, y * n, z * n);}
    Vector3 operator*(const long& n)          {return Vector3(x * n, y * n, z * n);}
    Vector3 operator*(const unsigned long& n) {return Vector3(x * n, y * n, z * n);}
    Vector3 operator*(const double& n)        {return Vector3(x * n, y * n, z * n);}

    Vector3 operator/(const Vector3& v){return Vector3(x / v.x, y / v.y, z / v.z);}
    Vector3 operator/(const int& n)           {return Vector3(x / n, y / n, z / n);}
    Vector3 operator/(const unsigned int& n)  {return Vector3(x / n, y / n, z / n);}
    Vector3 operator/(const long& n)          {return Vector3(x / n, y / n, z / n);}
    Vector3 operator/(const unsigned long& n) {return Vector3(x / n, y / n, z / n);}
    Vector3 operator/(const double& n)        {return Vector3(x / n, y / n, z / n);}

    Vector3 operator%(const Vector3& v){return Vector3(x % v.x, y % v.y, z % v.z);}
    Vector3 operator%(const int& n)           {return Vector3(x % n, y % n, z % n);}
    Vector3 operator%(const unsigned int& n)  {return Vector3(x % n, y % n, z % n);}
    Vector3 operator%(const long& n)          {return Vector3(x % n, y % n, z % n);}
    Vector3 operator%(const unsigned long& n) {return Vector3(x % n, y % n, z % n);}
    Vector3 operator%(const double& n)        {return Vector3(x % n, y % n, z % n);}

    //Assignment Operators
    Vector3& operator+=(const Vector3& v)       {x += v.x; y += v.y; z += v.z; return *this;}
    Vector3& operator+=(const int& n)           {x += n; y += n; z += n; return *this;}
    Vector3& operator+=(const unsigned int& n)  {x += n; y += n; z += n; return *this;}
    Vector3& operator+=(const long& n)          {x += n; y += n; z += n; return *this;}
    Vector3& operator+=(const unsigned long& n) {x += n; y += n; z += n; return *this;}
    Vector3& operator+=(const double& n)        {x += n; y += n; z += n; return *this;}

    Vector3& operator-=(const Vector3& v)       {x -= v.x; y -= v.y; z -= v.z; return *this;}
    Vector3& operator-=(const int& n)           {x -= n; y -= n; z -= n; return *this;}
    Vector3& operator-=(const unsigned int& n)  {x -= n; y -= n; z -= n; return *this;}
    Vector3& operator-=(const long& n)          {x -= n; y -= n; z -= n; return *this;}
    Vector3& operator-=(const unsigned long& n) {x -= n; y -= n; z -= n; return *this;}
    Vector3& operator-=(const double& n)        {x -= n; y -= n; z -= n; return *this;}

    Vector3& operator*=(const Vector3& v)       {x *= v.x; y *= v.y; z *= v.z; return *this;}
    Vector3& operator*=(const int& n)           {x *= n; y *= n; z *= n; return *this;}
    Vector3& operator*=(const unsigned int& n)  {x *= n; y *= n; z *= n; return *this;}
    Vector3& operator*=(const long& n)          {x *= n; y *= n; z *= n; return *this;}
    Vector3& operator*=(const unsigned long& n) {x *= n; y *= n; z *= n; return *this;}
    Vector3& operator*=(const double& n)        {x *= n; y *= n; z *= n; return *this;}

    Vector3& operator/=(const Vector3& v)       {x /= v.x; y /= v.y; z /= v.z; return *this;}
    Vector3& operator/=(const int& n)           {x /= n; y /= n; z /= n; return *this;}
    Vector3& operator/=(const unsigned int& n)  {x /= n; y /= n; z /= n; return *this;}
    Vector3& operator/=(const long& n)          {x /= n; y /= n; z /= n; return *this;}
    Vector3& operator/=(const unsigned long& n) {x /= n; y /= n; z /= n; return *this;}
    Vector3& operator/=(const double& n)        {x /= n; y /= n; z /= n; return *this;}

    Vector3& operator%=(const Vector3& v)       {x %= v.x; y %= v.y; z %= v.z; return *this;}
    Vector3& operator%=(const int& n)           {x %= n; y %= n; z %= n; return *this;}
    Vector3& operator%=(const unsigned int& n)  {x %= n; y %= n; z %= n; return *this;}
    Vector3& operator%=(const long& n)          {x %= n; y %= n; z %= n; return *this;}
    Vector3& operator%=(const unsigned long& n) {x %= n; y %= n; z %= n; return *this;}
    Vector3& operator%=(const double& n)        {x %= n; y %= n; z %= n; return *this;}

    String str(){
      return String(String(x) + "," + String(y) + "," + String(z));
    }
};
#endif