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
	//k1
		         particle[j].a1 = FGrav(particle[j], particle[i]) / particle[j].m;
		   	 particle[j].ax1 = particle[j].a * (particle[j].x - particle[i].x);
		   	 particle[j].ay1 = particle[j].a * (particle[j].y - particle[i].y);

			particle[j].vx1 = particle[j].vx;
			particle[j].vy1 = particle[j].vy;

			particle[j].x1 = particle[j].x;
			particle[j].y1 = particle[j].y;
	cout << particle[j].x1 << endl;
	//k2
			particle[j].vx2 = particle[j].vx1 + particle[j].ax1 * dt/2;
			particle[j].vy2 = particle[j].vy1 + particle[j].ay1 * dt/2;
			particle[j].x2 = particle[j].x1 + particle[j].vx2 * dt/2;
			particle[j].y2 = particle[j].y1 + particle[j].vy2 * dt/2;
			particle[j].ax2 = -G * particle[i].m * particle[j].x2 / cube(sqrt(sqr(particle[i].x1 - particle[j].x1) + sqr(particle[i].y1 - particle[j].y1)));
			particle[j].ax2 = -G * particle[i].m * particle[j].x2 / cube(sqrt(sqr(particle[i].x1 - particle[j].x1) + sqr(particle[i].y1 - particle[j].y1)));
	cout << particle[j].x2 << endl;

	//k3
			particle[j].vx3 = particle[j].vx1 + particle[i].ax2 * dt/2;
			particle[j].vy3 = particle[j].vy1 + particle[i].ay2 * dt/2;
			particle[j].x3 = particle[j].x1 + particle[j].vx3 * dt/2;
			particle[j].y3 = particle[j].y1 + particle[j].vy3 * dt/2;
			particle[j].ax3 = -G * particle[i].m * particle[j].x3 / cube(sqrt(sqr(particle[i].x2 - particle[j].x2) + sqr(particle[i].y2 - particle[j].y2)));
			particle[j].ay3 = -G * particle[i].m * particle[j].y3 / cube(sqrt(sqr(particle[i].x2 - particle[j].x2) + sqr(particle[i].y2 - particle[j].y2)));
	cout << particle[j].x3 << endl;
	//k4

			particle[j].vx4 = particle[j].vx1 + particle[j].ax3 * dt;
			particle[j].vy4 = particle[j].vy1 + particle[j].ax3 * dt;
			particle[j].x4 = particle[j].x1 + particle[j].vx4 * dt;
			particle[j].y4 = particle[j].y1 + particle[j].vy4 * dt;
			particle[j].ax4 = -G * particle[i].m * particle[j].x4 / cube(sqrt(sqr(particle[i].x3 - particle[j].x3) + sqr(particle[i].y3 - particle[j].y3)));
			particle[j].ay4 = -G * particle[i].m * particle[j].y4 / cube(sqrt(sqr(particle[i].x3 - particle[j].x3) + sqr(particle[i].y3 - particle[j].y3)));
	cout << particle[j].x4 << endl;
	        }

	    }

	for(int i = 0; i < elements; i++)
		{
	//	for(int j = 0; j < elements; j++)
	//		{
			particle[i].vx += dt/6 * (particle[i].ax1 + 2*particle[i].ax2 + 2*particle[i].ax3 + particle[i].ax4);
			particle[i].vy += dt/6 * (particle[i].ay1 + 2*particle[i].ay2 + 2*particle[i].ay3 + particle[i].ay4);
			particle[i].x += dt/6 * (particle[i].x1 + 2*particle[i].x2 + 2*particle[i].x3 + particle[i].x4);
			particle[i].y += dt/6 * (particle[i].y1 + 2*particle[i].y2 + 2*particle[i].y3 + particle[i].y4);

			simout << "#Telo#" << i << endl << particle[i].x << ", " << particle[i].y << endl;
	//		}
		}

	}
	simout.close();
return 0;
}
