#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

//Initialize various constants
const double a = 1.0;
const double q = 1.0;
const double m = 1.0;
const double E = 4.0;
const double V_scatter = 2.0;
const double hbar = 1.0;
const double C = 1.0;

double complex expo(double complex x0) {
	double complex result = 1;
	double complex x = 1;
	int f = 1;
	for (int i=1;i<21;i++) {
		x *= x0;
		f *= i;
		result += x/f;
	}
	return result;
}

//Potential function (scattering problem)
double V(double x) {
	if (x<=a && x>=0) {
		return V_scatter;
	} else {
		return 0;
	}
}

//Useful in Numerov algorithm
double k(double x) {
	return 2*m*(E-V(x))/(hbar*hbar);
}

int main(int argc, char* argv[]) {
	int N = atoi(argv[1]); //Represents resolution
	//Split space into discrete chunks, initialize phi
	double delX = a/N;
	double complex phi[9*N];
	for (int i=0;i<9*N;i++) {
		phi[i] = CMPLXF(0,0);
	}       
	
	printf("Finding initial values\n");
	//We will be calculating from -2a to 3a
	phi[5*N-1] = C*expo(I*q*a);
	phi[5*N] = C*expo(I*q*(a+delX));
	printf("Initial values: %lf+%lfi, %lf+%lfi\n", crealf(phi[5*N-1]), cimagf(phi[5*N-1]), crealf(phi[5*N]), cimagf(phi[5*N]));

	//Numerov algorithm
	double x = (N-1)*delX;
	for (int i=5*N-2;i>=0;i--) {
		phi[i] = ( (2 - 5*delX*delX*k(x)/6)*phi[i+1] - (1+delX*delX*k(x+delX)/12)*phi[i+2] ) / (1+delX*delX*k(x-delX)/12);
		x -= delX;
	}
	x = (N+1)*delX;
	for (int i=5*N+1;i<9*N;i++) {
		phi[i] = ( (2 - 5*delX*delX*k(x)/6)*phi[i-1] - (1+delX*delX*k(x-delX)/12)*phi[i-2] ) / (1+delX*delX*k(x+delX)/12);
		x += delX;
	}

	FILE* fPtr = fopen("phi.txt", "w");
	x = -4*a;
	for (int i=0;i<9*N;i++) {
		fprintf(fPtr, "%lf,%lf,%lf\n", x, crealf(phi[i]), cimagf(phi[i]));
		x += delX;
	}

	//Find tranmission & reflection probabilities
	//Note 4*N corresponds to the point x=0
	double AplusB = crealf(phi[4*N]);
	int index = (int) 4*N-M_PI/(2*q*delX);
	double AminusB = cimagf(phi[index]);
	double A = (AplusB + AminusB)/2;
	double B = (AplusB - AminusB)/2;
	printf("A = %lf, B = %lf, C = %lf\n", A, B, C);
	printf("R = %lf, T = %lf\n", B*B/(A*A), C*C/(A*A));
}
