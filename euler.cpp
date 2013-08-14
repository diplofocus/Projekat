#include <iostream>
#include <cmath>
#include <math.h>
#include <fstream>
#include <cstdlib>
#include <time.h>

using namespace std;

const int max_time = 1000;
const int elements = 2;
const double G = 6.67E-11;
const double h = 0.1;
const double dt = 1.0;
const double tmax = 1000;
 class pState
{
        public:
        double x,y;
        double vx,vy;
        double ax,ay,a;
        double m;

/*	pState()
	{
        x = rand() % 100 - 50;
        y = rand() % 100 - 50;
        vx = rand() % 10 - 5 ;
        vy = rand() % 10 - 5;
	m = rand() % 30 + 5;
	}
*/
};

double sqr(float a)
{
    return a * a;
}

double dist(pState A, pState B)
{
    return sqrt(sqr(B.x - A.x) + sqr(B.y - A.y));
}

double FGrav(pState A, pState B)
{
	double F = - G * A.m * B.m / sqr(dist(A, B));
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

	particle[0].x = 0;
	particle[0].y = 0;
	particle[0].vx = 0;
	particle[0].vy = 0;
	particle[0].m = 1.9E30;

	particle[1].x = 150E9;
	particle[1].y = 0;
	particle[1].vx = 0;
	particle[1].vy = 30E3;
	particle[1].m = 6E24;


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
		//Determining acceleration
	    for(int i = 0; i < elements; i++)
	    {
	        for(int j = 0; j < elements; j++)
	        {
			if(j==i)
			{
			continue;
			}
	//Acceleration
		         particle[j].a = FGrav(particle[i], particle[j]) / particle[j].m;
		   	 particle[j].ax = particle[j].a * (particle[j].x - particle[i].x) / dist(particle[j], particle[i]);
		   	 particle[j].ay = particle[j].a * (particle[j].y - particle[i].y) / dist(particle[j], particle[i]);

	        }
	      	 simout << "#Telo#" << i << endl << particle[i].x << ", " << particle[i].y << ",  " << particle[i].vx << ", " << particle[i].vy << ", " << particle[i].ax << ", " << particle[i].ay << ", " << particle[i].a << endl;

	    }

	for(int i = 0; i < elements; i++)
		{
		for(int j = 0; j < elements; j++)
			{
			particle[j].vx += particle[j].ax * dt;
			particle[j].vy += particle[j].ay * dt;
			particle[j].x += particle[j].vx * dt;
			particle[j].y += particle[j].vy * dt;
			}
		}

	}
	simout.close();
}
