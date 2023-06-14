#include <stdio.h>
#include <stdlib.h>
#include <fftw3.h>
#include <math.h>
#include <complex.h>

const double hbar = 1.0;
const double a = 0.05;
const double m = 1.0;

struct xPt {
	double x;
	double re;
	double im;
};
struct kPt {
	double k;
	double re;
	double im;
};

double V(double x) {
	return a*x*x;
	//if (x*x<9) {return 0;} else {return 1;}
	//if (x*x<1) {return 10000;} else {return 0;}
	//if (x>0) {return x;} else {return -x;}
}

int main(int argc, char* argv[]) {
	int Nx = atoi(argv[1]);
	double delX = atof(argv[2]);
	int Nt = atoi(argv[3]);
	double delT = atof(argv[4]);

	//Create V(x) file
	FILE* vPtr = fopen("Vx.txt", "w");

	//Set up fftw plans
	fftw_complex *in, *out;
        fftw_plan plan, back_plan;	
 	in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*Nx);
        out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*Nx);
        plan = fftw_plan_dft_1d(Nx, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
        back_plan = fftw_plan_dft_1d(Nx, out, in, FFTW_BACKWARD, FFTW_ESTIMATE);
	
	//Process generated xPsi[0]
	struct xPt xPsi[2*(Nt+1)][Nx];
	FILE* fPtr = fopen("psi.txt", "a+");
	for (int i=0;i<Nx;i++) {
		fscanf(fPtr, "%lf,%lf,%lf\n", &xPsi[0][i].x, &xPsi[0][i].re, &xPsi[0][i].im);
		fprintf(vPtr, "%lf\n", V(xPsi[0][i].x));
	}
	fclose(vPtr);
	double x = xPsi[0][0].x;
	
	//Initialize kPsi
	struct kPt kPsi[2*(Nt+1)][Nx];
	double kDel = 1/(Nx*delX);
	kPsi[0][0].k = -Nx*kDel/2;
	kPsi[0][0].re = 0;
	kPsi[0][0].im = 0;
	for (int i=1;i<Nx;i++) {
		kPsi[0][i].k = kPsi[0][i-1].k + kDel;
		kPsi[0][i].re = 0;
		kPsi[0][i].im = 0;
	}

	//Advance time operator by SOM
	//First half-step in position space
	float complex prevPt;
	float complex nextPt;
	for (int i=0;i<Nx;i++) {
		xPsi[1][i].x = xPsi[0][i].x;
		prevPt = xPsi[0][i].re+xPsi[0][i].im*I;
		nextPt = cexpf(-I*hbar*delT*V(xPsi[0][i].x)/2) * prevPt;
		xPsi[1][i].re = crealf(nextPt);
		xPsi[1][i].im = cimagf(nextPt);
		in[i][0] = xPsi[1][i].re;
		in[i][1] = xPsi[1][i].im;
		//fprintf(fPtr, "%lf,%lf,%lf\n", xPsi[1][i].x, xPsi[1][i].re, xPsi[1][i].im);
	}
	
	double normalizationY = (double) sqrt(Nx);
        //Convert to momentum space
        fftw_execute(plan);
	for (int i=0;i<Nx;i++) {
		out[i][0] /= normalizationY;
		out[i][1] /= normalizationY;
	}
	for (int i=0;i<Nx/2;i++) {
		kPsi[1][i].k = kPsi[0][i].k;
		kPsi[1][i].re = out[i+Nx/2][0];
		kPsi[1][i].im = out[i+Nx/2][1];
		//fprintf(fPtr, "%lf,%lf,%lf\n", kPsi[1][i].k, kPsi[1][i].re, kPsi[1][i].im);
	}
	for (int i=Nx/2;i<Nx;i++) {
		kPsi[1][i].k = kPsi[0][i].k;
		kPsi[1][i].re = out[i-Nx/2][0];
		kPsi[1][i].im = out[i-Nx/2][1];
		//fprintf(fPtr, "%lf,%lf,%lf\n", kPsi[1][i].k, kPsi[1][i].re, kPsi[1][i].im);
	}

	//Initial step in momentum space
	for (int i=0;i<Nx;i++) {
		kPsi[2][i].k = kPsi[1][i].k;
		prevPt = kPsi[1][i].re+kPsi[1][i].im*I;
		nextPt = cexpf(-I*hbar*delT*kPsi[2][i].k*kPsi[2][i].k/(2*m)) * prevPt;
		kPsi[2][i].re = crealf(nextPt);
		kPsi[2][i].im = cimagf(nextPt);
		//fprintf(fPtr, "%lf,%lf,%lf\n", kPsi[2][i].k, kPsi[2][i].re, kPsi[2][i].im);
	}

	//Convert back to position space
	for (int i=0;i<Nx/2;i++) {
		out[i+Nx/2][0] = kPsi[2][i].re;
		out[i+Nx/2][1] = kPsi[2][i].im;
		out[i][0] = kPsi[2][i+Nx/2].re;
		out[i][1] = kPsi[2][i+Nx/2].im;
	}
	fftw_execute(back_plan);
	for (int i=0;i<Nx;i++) {
		in[i][0] /= normalizationY;
		in[i][1] /= normalizationY;
		xPsi[2][i].x = xPsi[1][i].x;
		xPsi[2][i].re = in[i][0];
		xPsi[2][i].im = in[i][1];
		//fprintf(fPtr, "%lf,%lf,%lf\n", xPsi[2][i].x, xPsi[2][i].re, xPsi[2][i].im);
	}

	//Advance time
	for (int t=1;t<Nt;t++) {
	
	//Step in position space
	for (int i=0;i<Nx;i++) {
		xPsi[2*t+1][i].x = xPsi[2*t][i].x;
		prevPt = xPsi[2*t][i].re+xPsi[2*t][i].im*I;
		nextPt = cexpf(-I*hbar*delT*V(xPsi[2*t+1][i].x)/2) * prevPt;
		fprintf(fPtr, "%lf,%lf,%lf\n", xPsi[2*t+1][i].x, crealf(nextPt), cimagf(nextPt));
		nextPt = cexpf(-I*hbar*delT*V(xPsi[2*t+1][i].x)) * prevPt;
		xPsi[2*t+1][i].re = crealf(nextPt);
		xPsi[2*t+1][i].im = cimagf(nextPt);
		in[i][0] = xPsi[2*t+1][i].re;
		in[i][1] = xPsi[2*t+1][i].im;
	}
	
        //Convert to momentum space
        fftw_execute(plan);
	for (int i=0;i<Nx;i++) {
		out[i][0] /= normalizationY;
		out[i][1] /= normalizationY;
	}
	for (int i=0;i<Nx/2;i++) {
		kPsi[2*t+1][i].k = kPsi[2*t][i].k;
		kPsi[2*t+1][i].re = out[i+Nx/2][0];
		kPsi[2*t+1][i].im = out[i+Nx/2][1];
		//fprintf(fPtr, "%lf,%lf,%lf\n", kPsi[2*t+1][i].k, kPsi[2*t+1][i].re, kPsi[2*t+1][i].im);
	}
	for (int i=Nx/2;i<Nx;i++) {
		kPsi[2*t+1][i].k = kPsi[2*t][i].k;
		kPsi[2*t+1][i].re = out[i-Nx/2][0];
		kPsi[2*t+1][i].im = out[i-Nx/2][1];
		//fprintf(fPtr, "%lf,%lf,%lf\n", kPsi[2*t+1][i].k, kPsi[2*t+1][i].re, kPsi[2*t+1][i].im);
	}

	//Step in momentum space
	for (int i=0;i<Nx;i++) {
		kPsi[2*t+2][i].k = kPsi[2*t+1][i].k;
		prevPt = kPsi[2*t+1][i].re+kPsi[2*t+1][i].im*I;
		nextPt = cexpf(-I*hbar*delT*kPsi[2*t+2][i].k*kPsi[2*t+2][i].k/(2*m)) * prevPt;
		kPsi[2*t+2][i].re = crealf(nextPt);
		kPsi[2*t+2][i].im = cimagf(nextPt);
		//fprintf(fPtr, "%lf,%lf,%lf\n", kPsi[2*t+2][i].k, kPsi[2*t+2][i].re, kPsi[2*t+2][i].im);
	}

	//Convert back to position space
	for (int i=0;i<Nx/2;i++) {
		out[i+Nx/2][0] = kPsi[2*t+2][i].re;
		out[i+Nx/2][1] = kPsi[2*t+2][i].im;
		out[i][0] = kPsi[2*t+2][i+Nx/2].re;
		out[i][1] = kPsi[2*t+2][i+Nx/2].im;
	}
	fftw_execute(back_plan);
	for (int i=0;i<Nx;i++) {
		in[i][0] /= normalizationY;
		in[i][1] /= normalizationY;
		xPsi[2*t+2][i].x = xPsi[2*t+1][i].x;
		xPsi[2*t+2][i].re = in[i][0];
		xPsi[2*t+2][i].im = in[i][1];
		//fprintf(fPtr, "%lf,%lf,%lf\n", xPsi[2*t+2][i].x, xPsi[2*t+2][i].re, xPsi[2*t+2][i].im);
	}
	
	} //End time loop
	
	//Second half-step in position space
	for (int i=0;i<Nx;i++) {
		xPsi[2*Nt+1][i].x = xPsi[2*Nt][i].x;
		prevPt = xPsi[2*Nt][i].re+xPsi[2*Nt][i].im*I;
		nextPt = cexpf(-I*hbar*delT*V(xPsi[2*Nt+1][i].x)/2) * prevPt;
		xPsi[2*Nt+1][i].re = crealf(nextPt);
		xPsi[2*Nt+1][i].im = cimagf(nextPt);
		fprintf(fPtr, "%lf,%lf,%lf\n", xPsi[2*Nt+1][i].x, xPsi[2*Nt+1][i].re, xPsi[2*Nt+1][i].im);
	}

	fclose(fPtr);
	fftw_destroy_plan(plan);
	fftw_destroy_plan(back_plan);
	fftw_free(in);
	fftw_free(out);
	exit(0);
}
