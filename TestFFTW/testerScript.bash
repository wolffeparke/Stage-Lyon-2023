#!/bin/bash
gcc -o GenerateFunction GenerateFunction.c -lm
echo Successfully compiled function generator
N=200
./GenerateFunction $N
echo Generated Function
cat data.csv

gcc -I$HOME/usr/include fftwTest.c -L$HOME/usr/lib -lfftw3 -lm -o fftwTest
echo Compiled fftw code

./fftwTest $N
echo Computed transform
cat transformData.csv

./showPlots.py
