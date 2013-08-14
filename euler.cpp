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
const double dt = 1000.0;
const double tmax = 30E6;

 class pState
{
        public:
        double x,y;
	double x1,x2,x3,x4;
	double y1,y2,y3,y4;
        double vx,vy;
	double vx1,vx2,vx3,vx4;
	double vy1,vy2,vy3,vy4;
        double ax,ay,a;
	double ax1,ax2,ax3,ax4;
	double ay1,ay2,ay3,ay4;
	double a1,a2,a3,a4;
        double m;
/*
	pState()
	{
        x = rand() % 150000000;
        y = rand() % 150000000;
        vx = rand() % 15;
        vy = rand() % 15;
	m = rand() % 700000000000000000000000;
	}
*/
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
    return sqrt(sqr(B.x - A.x) + sqr(B.y - A.y));
}

double rdist()

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

	particle[0].x = 0;
	particle[0].y = 0;
	particle[0].vx = 0;
	particle[0].vy = 0;
	particle[0].m = 1.9E30;

	particle[1].x = 150E9;
	particle[1].y = 0;
	particle[1].vx = 0;
	particle[1].vy = 30E3;
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
		         particle[j].a1 = FGrav(particle[j], particle[i]) / particle[j].m;
		   	 particle[j].ax1 = particle[j].a * (particle[j].x - particle[i].x);
		   	 particle[j].ay1 = particle[j].a * (particle[j].y - particle[i].y);

			particle[j].vx1 = particle[j].vx;
			particle[j].vy1 = particle[j].vy;

			particle[j].x1 = particle[j].x;
			particle[j].y1 = particle[j].y;


			particle[j].a2 = -G * particle[i].m * particle[j].x2 / (cube(dist(particle[j], particle[i])));
	        }

	    }

	for(int i = 0; i < elements; i++)
		{
		for(int j = 0; j < elements; j++)
			{
			particle[j].vx += particle[j].ax * dt;
			particle[j].vy += particle[j].ay * dt;
			particle[j].x += particle[j].vx * dt;
			particle[j].y += particle[j].vy * dt;
			 simout << "#Telo#" << i << endl << particle[i].x << ", " << particle[i].y << ",  " << endl;
			}
		}

	}
	simout.close();
return 0;
}
