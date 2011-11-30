/**
Description: Leapfrog for a 1-D coupled harmonic oscillator
author: Carlos Olivares
e-mail: alfaceor@gmail.com
creative commons
*/

#include <iostream>
using namespace std;

#define DIM 3
#define N 2

void print_array(double arg[],int length) {
	for (int i=0; i<length; i++){
		cout<< arg[i]<<"\t";
	}
	cout<<endl;
}

int main(){

	// Initialize variables
	double r[N][DIM]= {{0,0,0},{0,10,0}};	// position
	double v[N][DIM]= {{0,0,0},{0,0,0}};		// velocity
	double a[N][DIM]= {{0,0,0},{0,0,0}};	// aceleration
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
	//---> BEGIN _Integrator leapfrog_
	int n=1;
	while(t_f>=t_i){
	cout<<"MODEL\t"<< n <<"\n";
		for(int i=0;i<N;i++){
			if (i==0)
				cout <<"ATOM\t"<<(i+1) << "\t"<<"CA\t"<<"MET A 1\t";
			else
				cout <<"ATOM\t"<<(i+1) << "\t"<<"C\t"<<"MET A 1\t";

			for (int d=0;d<DIM;d++){
				// calculate the aceleration (force) over the particle
				
				if(d==0)
					a[i][d] =  k[0]*(r[i+1][d]-r[i][d]-l[0])/mass[0];
				//else
					//a[i][d] = -k[0]*(r[i][d]-r[i-1][d]-l[0])/mass[0];	
				// generate the new velocity
				v[i][d] += a[i][d] * dt;
				// actualize the position
				r[i][d] += v[i][d] * dt;  // where v[i] is v_(t+1/2 * dt)
				cout << r[i][d] << "\t";
			}
			if(i==0)	
				cout<<"1.00\t0.43\tC"<<endl;
			else
				cout<<"1.00\t0.41\tC"<<endl;
		}
		cout<<"ENDMDL"<<endl;
		t_i  += dt;
		n++;
	}
	//---> END _Integrator leapfrog_
}
