#include <stdio.h>
#include <fftw3.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv) {
	//Initialize fftw plan
	fftw_complex *in, *out;
	fftw_plan plan, back_plan;
  	int N = atoi(argv[1]);
	in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*N);
	out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*N);
	plan = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
	back_plan = fftw_plan_dft_1d(N, out, out, FFTW_BACKWARD, FFTW_ESTIMATE);

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

	//Compute transform in-place
	fftw_execute(plan);
	//fftw_execute(back_plan);

	double normalizationY = (double) N/2;
	double stepX = 2/(x[N] - x[0]);
	double X = -N*stepX/2;
	for (int i=N/2;i<N;i++) {
		out[i][0] /= normalizationY;
		fprintf(outPtr, "%lf,%lf\n", X, fabs(out[i][0]));
		X += stepX;
	}
	X = 0;
	for (int i=0;i<N/2;i++) {
		out[i][0] /= normalizationY;
		fprintf(outPtr, "%lf,%lf\n", X, fabs(out[i][0]));
		X += stepX;
	}
	fclose(outPtr);
	
	fftw_destroy_plan(plan);
	fftw_free(in);
	fftw_free(out);
}
