
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

const double TAU = M_PI;
double function(double x, double A, double b) {
	double result = A*exp(-b*x*x);
	//double result = cos(TAU*x)+2*cos(2*TAU*x);
	//double result = sin(10*x)/(10*x);
	return result;	
}

int main(int argc, char *argv[]) {
	double sigma=2;
	double A = 1;
	double b = 1;
	
	FILE* fPtr = NULL;
	fPtr = fopen("data.csv", "w");

	if (fPtr == NULL) {
		printf("Unable to create file\n");
		exit(EXIT_FAILURE);
	} 
	printf("Creating Datapoints\n");
	int N = atoi(argv[1]);
	double x = -10.0;
	for (int i=0;i<N+1;i++) {
		fprintf(fPtr, "%f,%f\n", x, function(x, A, b));
		x += 20.0/N;
	}
	fclose(fPtr);
	return 0;
}
