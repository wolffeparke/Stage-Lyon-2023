# Stage-Lyon-2023
Each algo is located in a separate directory and can be directly executed using "./testerScript.bash"

TestFFTW contains the initial program testing the implementation of fftw for fourier transforms. Change the generated function in GenerateFunction.c, run the program, the plots shown are the original function, the transform, then the inverse transform (which should give back the original function)

Numerov1d is an abandoned project for solving the time-independent Schrödinger equation using the numerov algorithm. Results are sometimes good but often not physically meaningful.

SOM1d implements the split operator method for solving the time-dependent Schrödinger equation in 1d. Change the initial state in generateFunction.c, change the potential function in som.c, and edit the settings of the algo in testerScript.bash (such as time intervals, space intervals, gif settings). The program generates a gif showing the evolution of the system under the given conditions.

SavedResults is a compilation of notable gifs and images from various programs.
