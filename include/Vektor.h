#ifndef __VEKTOR_H__
#define __VEKTOR_H__

#include <iostream> 
#include <cmath>

class Vektor {

 public:
  double x, y, z;

  Vektor(double _x, double _y, double _z) {
    this->x = _x;
    this->y = _y;
    this->z = _z;
  }
  
  Vektor() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
  }

  Vektor& operator*=(const double& scalar) {
    this->x *= scalar;
    this->y *= scalar;
    this->z *= scalar;
    return *this;
  }

  Vektor& operator*(const double& scalar) {
    this->x * scalar;
    this->y * scalar;
    this->z * scalar;
    return *this;
  }

  Vektor& operator+=(const Vektor& v) {
    this->x += v.x;
    this->y += v.y;
    this->z += v.z;
    return *this;
  }

  Vektor operator-(const Vektor& v) {
    Vektor r;
    r.x = this->x - v->x;
    r.y = this->y - v->y;
    r.z = this->z - v->z;
    return r;
  }
    

  double intenzitet() {
    return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
  }
};

std::ostream& operator<<(std::ostream& os, const Vektor& v);

#endif
