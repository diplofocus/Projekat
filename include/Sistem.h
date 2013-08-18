#ifndef __SISTEM_H__
#define __SISTEM_H__

#include "Telo.h"

static const int N = 2;

class Sistem {

 public:
  Telo **tela;

  Sistem() {
    tela = new Telo*[N];
    for(int i = 0; i < N; i++) {
      tela[i] = new Telo(this);
    }
  }

  ~Sistem() {
    for(int i = 0; i < N; i++) {
      delete tela[i];
    }

  }
};

#endif
