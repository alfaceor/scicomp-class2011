/**
Description: Leapfrog for a 1-D coupled harmonic oscillator
author: Carlos Olivares
e-mail: alfaceor@gmail.com
license: creative commons
*/
#include <stdio.h>
#include <math.h>
#include "pdb_utils.hpp"
//#include <iostream>
//using namespace std;

#define DIM 3
#define N 4  // Number of particles

int main(){

	// Initialize variables
	double r[N][DIM]= {{0,0,0},{0,10,0},{0,20,0},{0,30,0}};	// position
	double v[N][DIM]= {{0,0,0},{0,0,0},{0,0,0},{0,0,0}};		// velocity
	double a[N][DIM]= {{0,0,0},{0,0,0},{0,0,0},{0,0,0}};	// aceleration
	// System properties
	double mass[N] = {1,1,1,1};
	double k[N-1] = {100,100,100};		// hooke constant
	double l[N-1] = {5,5,5};		// natural length


	// auxiliar variables
	double xi[N-1][DIM];			// spring deformation vector
		
	// Integration parameters
	int n_steps=100;	// iteration steps
	double t_f=5;			// initial time
	double t_i=0;			// final time
	double dt=(t_f - t_i)/n_steps;
	
	// TODO: generalize this, and make a function.
	//---> BEGIN _Integrator leapfrog_
	int n=1;
	while(t_f>=t_i){
		// ---> BEGIN spring deformation
		for(int s=0;s<N-1;s++){
			double norm_xi;		// deformation length
			for (int d=0;d<DIM;d++){
				xi[s][d] = (r[s][d]-r[s+1][d]);	// temporal data, delta r
				norm_xi += xi[s][d]*xi[s][d]; 	// quadratic sum
			}
			norm_xi=sqrt(norm_xi);

			for (int d=0;d<DIM;d++){		
				xi[s][d] = xi[s][d] * (1-l[s]/norm_xi);		// real deformation values
			}
			// finally the spring deformation is xi[s][d] = (r[s][d]-r[s+1][d])*(1-l[s]/norm_xi);
		}
		// ---> END spring deformation
		
		printf("MODEL\t%d\n",n);		// Time step for the pdb file
		for(int i=0;i<N;i++){
			for (int d=0;d<DIM;d++){
				// aceleration (force) over the particle by the SPRINGS
				if(i==0)
					a[i][d] = (-xi[i][d]) * (k[i]/mass[i]);
				else if (i==N)
					a[i][d] = (xi[i-1][d])* (k[i-1]/mass[i]);
				else
					a[i][d] = (-xi[i][d]) * (k[i]/mass[i])+xi[i-1][d]*(k[i]/mass[i]);
					
				// generate the new velocity
				v[i][d] += a[i][d] * dt;
				// actualize the position
				r[i][d] += v[i][d] * dt;  // where v[i] is v_(t+1/2 * dt)
			}
			print_pdb_line(i+1,r[i][0],r[i][1],r[i][2]);
		}
		printf("ENDMDL\n");
		t_i  += dt;
		n++;
	}
	//---> END _Integrator leapfrog_
}
