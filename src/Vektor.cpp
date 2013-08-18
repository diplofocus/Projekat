#include <iostream>

#include "Vektor.h"

using namespace std;

std::ostream& operator<<(std::ostream& os, const Vektor& v) {
  return os << v.x << '\t' << v.y << '\t' << v.z;
}
