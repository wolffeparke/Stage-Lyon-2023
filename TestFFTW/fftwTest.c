#include <stdio.h>
#include <fftw3.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv) {
	//Initialize fftw plan
	fftw_complex *in, *out;
	fftw_plan plan, back_plan;
  	int N = atoi(argv[1]);
	double xMax = atof(argv[2]);
	in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*N);
	out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*N);
	plan = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
	back_plan = fftw_plan_dft_1d(N, out, in, FFTW_BACKWARD, FFTW_ESTIMATE);

	//Open data file
	FILE* fPtr = NULL;
	fPtr = fopen("data.csv", "r");
	if (fPtr == NULL) {
		printf("Unable to open data file\n");
		exit(EXIT_FAILURE);
	}
	FILE* outPtr = NULL;
	outPtr = fopen("transformData.csv", "w");
	if (outPtr == NULL) {
		printf("Unable to open output file\n");
		exit(EXIT_FAILURE);
	}
	
	//Initialize data
	double x[N+1];
	double y;
	for (int i=0;i<N;i++) {
		fscanf(fPtr, "%lf,%lf\n", &x[i], &y);
		in[i][0] = y;
		in[i][1] = 0;
	}
	fscanf(fPtr, "%lf,%lf\n", &x[N], &y);
	fclose(fPtr);

	double normalizationY = (double) sqrt(N);
	//Compute forward transform
	printf("Computing transform\n");
	fftw_execute(plan);

	double delK = 1/(2*xMax);
	double k = -N*delK/2;
	printf("Normalization\n");
	for (int i=N/2;i<N;i++) {
		out[i][0] /= normalizationY;
		out[i][1] /= normalizationY;
		fprintf(outPtr, "%lf,%lf,%lf\n", k, out[i][0], out[i][1]);
		k += delK;
	}
	k = 0;
	for (int i=0;i<N/2;i++) {
		out[i][0] /= normalizationY;
		out[i][1] /= normalizationY;
		fprintf(outPtr, "%lf,%lf,%lf\n", k, out[i][0], out[i][1]);
		k += delK;
	}
	
	//Compute inverse transform
	printf("Computing inverse transform\n");
	fftw_execute(back_plan);
	double delX = 2*xMax/N;
	double X = -xMax;
	printf("Normalization\n");
	for (int i=0;i<N;i++) {
		in[i][0] /= normalizationY;
		in[i][1] /= normalizationY;
		fprintf(outPtr, "%lf,%lf,%lf\n", X, in[i][0], in[i][1]);
		X += delX;
	}

	printf("Freeing resources");
	fclose(outPtr);
	
	fftw_destroy_plan(plan);
	fftw_destroy_plan(back_plan);
	fftw_free(in);
	fftw_free(out);
	exit(0);
}
