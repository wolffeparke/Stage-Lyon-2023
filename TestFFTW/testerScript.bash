#!/bin/bash
gcc -o GenerateFunction GenerateFunction.c -lm
echo Successfully compiled function generator
N=500
xMax=20.0
./GenerateFunction $N $xMax
echo Generated Function
cat data.csv

gcc -I$HOME/usr/include fftwTest.c -L$HOME/usr/lib -lfftw3 -lm -o fftwTest
echo Compiled fftw code

./fftwTest $N $xMax
echo Computed transform

./showPlots.py $N $xMax
