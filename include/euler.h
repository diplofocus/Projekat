#ifndef __EULER_H__
#define __EULER_H__
#include <iostream>
#include "Telo.h"
#include "Sistem.h"
#include "Vektor.h"
#include <cmath>
#include <fstream>

using namespace std;

const double G = 6.67E-11;
const double tmax = 5E7;
const double dt = 1E3;

void euler(Sistem* a)
{
ofstream output;
output.open("output.txt");

  for(double t = 0; t < tmax; t += dt)
  {
    for(int i = 0; i < N; i++)
    {
		for(int j = 0; i < N; j++)
		{
			a->tela[j]->a += -G * a->tela[i]->m / pow(tela[i]->intenzitet()) - tela[j]->intenzitet()), 3);
			a->tela[j]->v += tela[j]->a * dt;
			a->tela[j]->r += tela[j]->v * dt;
		}
    }
	for(int i = 0; i < N; i++)
	{
		output << a->tela[i]->r->x << ", " << a->tela[i]->r->y << ", " << a->tela[i]->r->z << endl;
	}
  }
}
#endif
