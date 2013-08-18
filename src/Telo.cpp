#include <cmath>

#include "Telo.h"

Vektor Telo::ubrzanje() {

  for(int i = 0; i < N; i++) {
    if(this != this->sistem->tela[i]) {
      // ovo je zapravo radijus vektor
      Vektor a = this->r - this->sistem->tela[i]->r;
      a *= - GAMMA * this->sistem->tela[i]->m / pow(r.intenzitet(), 3);
    }
  }
}
