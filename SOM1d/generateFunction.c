
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

const double TAU = 2*M_PI;
const double sigma=2;
const double K = 1;
const double a = 1;
const double b = 8.4;
const double c = -18;

double function(double x) {
	double result = K*exp(-a*x*x+b*x+c);
	//double result = cos(TAU*x);
	//double result = sin(a*M_PI*x)/(a*M_PI*x);
	//result = result*result;
	return result;	
}

int main(int argc, char *argv[]) {
	
	FILE* fPtr = fopen("psi.txt", "w");

	printf("Creating Datapoints\n");
	int N = atoi(argv[1]);
	double delX = atof(argv[2]);
	double xMax = N*delX/2;
	double x = -xMax;
	for (int i=0;i<N+1;i++) {
		fprintf(fPtr, "%f,%f,0\n", x, function(x));
		x += delX;
	}
	fclose(fPtr);
	return 0;
}
