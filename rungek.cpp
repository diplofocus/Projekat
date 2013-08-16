#include <iostream>
#include <cmath>
#include <math.h>
#include <fstream>
#include <cstdlib>
#include <time.h>

using namespace std;

const int elements = 2;
const double G = 6.67E-11;
const double h = 0.1;
const double dt = 1000;
const double tmax = 30E6;

struct vect
{
  public:
  double x,y,z;
};

 class pState
{
        public:
        vect r;
        vect v;
        vect a;
        vect a1,a2,a3,a4;
        vect r1,r2,r3,r4;
        vect v1,v2,v3,v4;
        vect F;
        double m;
};

double sqr(float a)
{
    return a * a;
}

double cube(float a)
{
	return a * a * a;
}

double dist(pState A, pState B)
{
    return sqrt(sqr(B.r.x - A.r.x) + sqr(B.r.y - A.r.y));
}

double FGrav(pState A, pState B)
{
	double F = - G * A.m * B.m / cube(dist(A, B));
	return F;
}

int main()
{
	ofstream simout;
	simout.open("output.txt");

    pState particle[elements];

    for(int i = 0; i < elements; i++)
    {
	particle[i] = pState();
    }

	particle[0].r.x = 0;
	particle[0].r.y = 0;
	particle[0].v.x = 0;
	particle[0].v.y = 0;
	particle[0].m = 1.9E30;

	particle[1].r.x = 150E9;
	particle[1].r.y = 0;
	particle[1].v.x = 0;
	particle[1].v.y = 30E3;
	particle[1].m = 8E24;


	double perc = 0;
	int currPerc = 0;
	for(double t = 0; t <= tmax; t += dt)
	{
		if(perc >= tmax / 100)
		{
			cout.flush();
			currPerc++;
			cout << currPerc << endl;
			perc=0;
		}
		perc += dt;

	    for(int i = 0; i < elements; i++)
	    {
	        for(int j = 0; j < elements; j++)
	        {
			if(j==i)
			{
			continue;
			}
	//k1
            particle[j].a1.x = -G * particle[i].m * (particle[i].r.x - particle[j].r.x) / cube(dist(particle[i], particle[j]));
            particle[j].a1.y = -G * particle[i].m * (particle[i].r.y - particle[j].r.y) / cube(dist(particle[i], particle[j]));
            particle[j].r1 = particle[j].r;
            particle[j].v1 = particle[j].v;

	        }

            for(int j = 0; j < elements; j++)
	        {
			if(j==i)
			{
			continue;
			}
	//k2

            particle[j].v2.x = particle[j].v1.x + particle[j].a1.x * dt / 2;
            particle[j].v2.y = particle[j].v1.y + particle[j].a1.y * dt / 2;
            particle[j].r2.x = particle[j].r1.x + particle[j].v2.x * dt / 2;
            particle[j].r2.y = particle[j].r1.y + particle[j].v2.y * dt / 2;
            particle[j].a2.x = -G * particle[i].m * (particle[j].r2.x - particle[i].r2.x) / cube(dist(particle[i], particle[j]));
            particle[j].a2.y = -G * particle[i].m * (particle[j].r2.y - particle[i].r2.y) / cube(dist(particle[i], particle[j]));
	        }

            for(int j = 0; j < elements; j++)
	        {
			if(j==i)
			{
			continue;
			}
	//k3

            particle[j].v3.x = particle[j].v1.x + particle[j].a2.x * dt / 2;
            particle[j].v3.y = particle[j].v1.y + particle[j].a2.y * dt / 2;
            particle[j].r3.x = particle[j].r1.x + particle[j].v3.x * dt / 2;
            particle[j].r3.y = particle[j].r1.y + particle[j].v3.y * dt / 2;
            particle[j].a3.x = -G * particle[i].m * (particle[j].r3.x - particle[i].r3.x) / cube(sqrt(sqr(particle[j].r2.x) + sqr(particle[j].r2.y)));
            particle[j].a3.x = -G * particle[i].m * (particle[j].r3.y - particle[i].r3.y) / cube(sqrt(sqr(particle[j].r2.x) + sqr(particle[j].r2.y)));
	        }

            for(int j = 0; j < elements; j++)
	        {
			if(j==i)
			{
			continue;
			}
	//k4

            particle[j].v4.x = particle[j].v1.x + particle[j].a3.x * dt;
            particle[j].v4.y = particle[j].v1.y + particle[j].a3.y * dt;
            particle[j].r4.x = particle[j].r1.x + particle[j].v4.x * dt;
            particle[j].r4.y = particle[j].r1.y + particle[j].v4.y * dt;
            particle[j].a4.x = -G * particle[i].m * (particle[i].r4.x - particle[j].r4.x) / cube(sqrt(sqr(particle[i].r3.x - particle[j].r3.x) + sqr(particle[i].r3.y - particle[j].r3.x)));
            particle[j].a4.x = -G * particle[i].m * (particle[i].r4.y - particle[j].r4.y) / cube(sqrt(sqr(particle[i].r3.x - particle[j].r3.y) + sqr(particle[i].r3.y - particle[j].r3.y)));
	        }


	    }

	for(int i = 0; i < elements; i++)
		{
	//	for(int j = 0; j < elements; j++)
	//		{
			particle[i].v.x += dt/6.0 * (particle[i].a1.x + 2*particle[i].a2.x + 2*particle[i].a3.x + particle[i].a4.x);
			particle[i].v.y += dt/6.0 * (particle[i].a1.y + 2*particle[i].a2.y + 2*particle[i].a3.y + particle[i].a4.y);
			particle[i].r.x += dt/6.0 * (particle[i].r1.x + 2*particle[i].r2.x + 2*particle[i].r3.x + particle[i].r4.x);
			particle[i].r.y += dt/6.0 * (particle[i].r1.y + 2*particle[i].r2.y + 2*particle[i].r3.y + particle[i].r4.y);

			simout << "#Telo#" << i << endl << particle[i].r.x << ", " << particle[i].r.y << endl;
	//		}
		}

	}
	simout.close();
return 0;
}
