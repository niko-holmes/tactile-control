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
    vector3 operator+(const vector3& v){return vector3(x + v.x, y + v.y, z + v.z);}
    vector3 operator-(const vector3& v){return vector3(x - v.x, y - v.y, z - v.z);}
    vector3 operator*(const vector3& v){return vector3(x * v.x, y * v.y, z * v.z);}
    vector3 operator/(const vector3& v){return vector3(x / v.x, y / v.y, z / v.z);}
    vector3 operator%(const vector3& v){return vector3(x % v.x, y % v.y, z % v.z);}

    //Assignment Operators
    vector3& operator+=(const vector3& v){
      x += v.x;
      y += v.y;
      z += v.z;
      return *this;
    }
    vector3& operator-=(const vector3& v){
      x -= v.x;
      y -= v.y;
      z -= v.z;
      return *this;
    }
    vector3& operator*=(const vector3& v){
      x *= v.x;
      y *= v.y;
      z *= v.z;
      return *this;
    }
    vector3& operator/=(const vector3& v){
      x /= v.x;
      y /= v.y;
      z /= v.z;
      return *this;
    }
    vector3& operator%=(const vector3& v){
      x %= v.x;
      y %= v.y;
      z %= v.z;
      return *this;
    }

    String str(){
      return String(String(x) + "," + String(y) + "," + String(z));
    }
};
#endif