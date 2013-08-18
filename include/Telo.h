#ifndef __TELO_H__
#define __TELO_H__

#include "Vektor.h"

class Telo {
  
 public:
  Vektor r;
  Vektor v;
  Vektor a;
  double m;

  Sistem* sistem;

  Telo(Sistem* sistem) {
    this->sistem = sistem;
  }
  
  Vektor ubrzanje();

  Telo(Vektor& r, Vektor &v, Vektor &a , double m) {
    this->r = r;
    this->v = v;
    this->m = m;
    this->a = a;
  }
};

#endif
