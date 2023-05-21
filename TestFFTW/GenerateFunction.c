
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

const double TAU = 2*M_PI;
const double sigma=2;
const double K = 1;
const double a = 10;
const double b = 6.5;
const double c = -0.5;

double function(double x) {
	double result = K*exp(-a*x*x+b*x+c);
	//double result = cos(TAU*x)+2*cos(2*TAU*x)+3*sin(3*TAU*x);
	//double result = sin(a*M_PI*x)/(a*M_PI*x);
	//result = result*result;
	return result;	
}

int main(int argc, char *argv[]) {
	
	FILE* fPtr = fopen("data.csv", "w");

	printf("Creating Datapoints\n");
	int N = atoi(argv[1]);
	double x = -10.0;
	for (int i=0;i<N+1;i++) {
		fprintf(fPtr, "%f,%f\n", x, function(x));
		x += 20.0/N;
	}
	fclose(fPtr);
	return 0;
}
