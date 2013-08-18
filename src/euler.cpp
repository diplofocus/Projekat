#include <iostream>
#include <math.h>

#include "Telo.h"
#include "Sistem.h"
#include "euler.h"

using namespace std;

int main() {

  Sistem *s = new Sistem();
  Vektor rSunca(0 ,0 ,0);
  Vektor vSunca(0, 0, 0);
  double mSunca = 1.9E30;
  Vektor rZemlje(0, 0, 0);
  Vektor vZemlje(30E3, 0, 0);
  double mZemlje = 6E24;
	s->tela[0]->r = rSunca;
	s->tela[0]->v = vSunca;
	s->tela[0]->m = mSunca;
	s->tela[1]->r = rZemlje;
	s->tela[1]->v = vZemlje;
	s->tela[1]->m = mZemlje;

  euler(s);
   delete s;
}
