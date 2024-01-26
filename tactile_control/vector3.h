#ifndef vector3_h
#define vector3_h

template <typename T>
class vector3
{
  public:
    T x, y, z;

    //Constructors
    vector3(T x = 0, T y = 0, T z = 0){
      this->x = x;
      this->y = y;
      this->z = z;
    }

    //Binary Arithmetic Operators
    vector3 operator+(const vector3& v)       {return vector3(x + v.x, y + v.y, z + v.z);}
    vector3 operator+(const int& n)           {return vector3(x + n, y + n, z + n);}
    vector3 operator+(const unsigned int& n)  {return vector3(x + n, y + n, z + n);}
    vector3 operator+(const long& n)          {return vector3(x + n, y + n, z + n);}
    vector3 operator+(const unsigned long& n) {return vector3(x + n, y + n, z + n);}
    vector3 operator+(const double& n)        {return vector3(x + n, y + n, z + n);}

    vector3 operator-(const vector3& v){return vector3(x - v.x, y - v.y, z - v.z);}
    vector3 operator-(const int& n)           {return vector3(x - n, y - n, z - n);}
    vector3 operator-(const unsigned int& n)  {return vector3(x - n, y - n, z - n);}
    vector3 operator-(const long& n)          {return vector3(x - n, y - n, z - n);}
    vector3 operator-(const unsigned long& n) {return vector3(x - n, y - n, z - n);}
    vector3 operator-(const double& n)        {return vector3(x - n, y - n, z - n);}

    vector3 operator*(const vector3& v){return vector3(x * v.x, y * v.y, z * v.z);}
    vector3 operator*(const int& n)           {return vector3(x * n, y * n, z * n);}
    vector3 operator*(const unsigned int& n)  {return vector3(x * n, y * n, z * n);}
    vector3 operator*(const long& n)          {return vector3(x * n, y * n, z * n);}
    vector3 operator*(const unsigned long& n) {return vector3(x * n, y * n, z * n);}
    vector3 operator*(const double& n)        {return vector3(x * n, y * n, z * n);}

    vector3 operator/(const vector3& v){return vector3(x / v.x, y / v.y, z / v.z);}
    vector3 operator/(const int& n)           {return vector3(x / n, y / n, z / n);}
    vector3 operator/(const unsigned int& n)  {return vector3(x / n, y / n, z / n);}
    vector3 operator/(const long& n)          {return vector3(x / n, y / n, z / n);}
    vector3 operator/(const unsigned long& n) {return vector3(x / n, y / n, z / n);}
    vector3 operator/(const double& n)        {return vector3(x / n, y / n, z / n);}

    vector3 operator%(const vector3& v){return vector3(x % v.x, y % v.y, z % v.z);}
    vector3 operator%(const int& n)           {return vector3(x % n, y % n, z % n);}
    vector3 operator%(const unsigned int& n)  {return vector3(x % n, y % n, z % n);}
    vector3 operator%(const long& n)          {return vector3(x % n, y % n, z % n);}
    vector3 operator%(const unsigned long& n) {return vector3(x % n, y % n, z % n);}
    vector3 operator%(const double& n)        {return vector3(x % n, y % n, z % n);}

    //Assignment Operators
    vector3& operator+=(const vector3& v)       {x += v.x; y += v.y; z += v.z; return *this;}
    vector3& operator+=(const int& n)           {x += n; y += n; z += n; return *this;}
    vector3& operator+=(const unsigned int& n)  {x += n; y += n; z += n; return *this;}
    vector3& operator+=(const long& n)          {x += n; y += n; z += n; return *this;}
    vector3& operator+=(const unsigned long& n) {x += n; y += n; z += n; return *this;}
    vector3& operator+=(const double& n)        {x += n; y += n; z += n; return *this;}

    vector3& operator-=(const vector3& v)       {x -= v.x; y -= v.y; z -= v.z; return *this;}
    vector3& operator-=(const int& n)           {x -= n; y -= n; z -= n; return *this;}
    vector3& operator-=(const unsigned int& n)  {x -= n; y -= n; z -= n; return *this;}
    vector3& operator-=(const long& n)          {x -= n; y -= n; z -= n; return *this;}
    vector3& operator-=(const unsigned long& n) {x -= n; y -= n; z -= n; return *this;}
    vector3& operator-=(const double& n)        {x -= n; y -= n; z -= n; return *this;}

    vector3& operator*=(const vector3& v)       {x *= v.x; y *= v.y; z *= v.z; return *this;}
    vector3& operator*=(const int& n)           {x *= n; y *= n; z *= n; return *this;}
    vector3& operator*=(const unsigned int& n)  {x *= n; y *= n; z *= n; return *this;}
    vector3& operator*=(const long& n)          {x *= n; y *= n; z *= n; return *this;}
    vector3& operator*=(const unsigned long& n) {x *= n; y *= n; z *= n; return *this;}
    vector3& operator*=(const double& n)        {x *= n; y *= n; z *= n; return *this;}

    vector3& operator/=(const vector3& v)       {x /= v.x; y /= v.y; z /= v.z; return *this;}
    vector3& operator/=(const int& n)           {x /= n; y /= n; z /= n; return *this;}
    vector3& operator/=(const unsigned int& n)  {x /= n; y /= n; z /= n; return *this;}
    vector3& operator/=(const long& n)          {x /= n; y /= n; z /= n; return *this;}
    vector3& operator/=(const unsigned long& n) {x /= n; y /= n; z /= n; return *this;}
    vector3& operator/=(const double& n)        {x /= n; y /= n; z /= n; return *this;}

    vector3& operator%=(const vector3& v)       {x %= v.x; y %= v.y; z %= v.z; return *this;}
    vector3& operator%=(const int& n)           {x %= n; y %= n; z %= n; return *this;}
    vector3& operator%=(const unsigned int& n)  {x %= n; y %= n; z %= n; return *this;}
    vector3& operator%=(const long& n)          {x %= n; y %= n; z %= n; return *this;}
    vector3& operator%=(const unsigned long& n) {x %= n; y %= n; z %= n; return *this;}
    vector3& operator%=(const double& n)        {x %= n; y %= n; z %= n; return *this;}

    String str(){
      return String(String(x) + "," + String(y) + "," + String(z));
    }
};
#endif