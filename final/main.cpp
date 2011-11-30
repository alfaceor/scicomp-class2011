/**
Description: Leapfrog for a 1-D coupled harmonic oscillator
author: Carlos Olivares
e-mail: alfaceor@gmail.com
creative commons
*/


#include <iostream>
using namespace std;

#define N 2

void print_array(double arg[],int length) {
	for (int i=0; i<length; i++){
		cout<< arg[i]<<"\t";
	}
	cout<<endl;
}

int main(){

	// Initialize variables
	double r[N] = {0,10};	// position
	double v[N] = {0,0};		// velocity
	double a[N] = {1,0};							// aceleration
	// System properties
	double k[N-1] = {1};		// hooke constant
	double l[N-1] = {5};	// natural length
	double mass[N] = {1,1};
	
	
	// Integration parameters
	int n_steps=100;	// iteration steps
	double t_f=5;		// initial time
	double t_i=0;		// final time
	double dt=(t_f - t_i)/n_steps;
	
	// TODO: generalize this, and make a function.
	while(t_f>=t_i){
	//---> BEGIN _Integrator leapfrog_
	//	int i=0;
		for(int i=0;i<N;i++){
			// calculate the aceleration (force) over the particle
			if(i==0)
				a[i]=k[i]*(r[i+1]-r[i]-l[i])/mass[i];
			else
				a[i]=-k[i-1]*(r[i]-r[i-1]-l[i-1])/mass[i];	
			// generate the new velocity
			v[i] += a[i] * dt;
			// actualize the position
			r[i] += v[i]*dt;  // where v[i] is v_(t+1/2 * dt)
		}
	//---> END _Integrator leapfrog_
		cout<<t_i<<"\t";
		print_array(r,N);
		t_i  += dt;
	}
	

//Print position and velocities.

}
