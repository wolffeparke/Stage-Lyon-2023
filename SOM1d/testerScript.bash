#!/bin/bash
rm psi.txt
gcc -o GenerateFunction generateFunction.c -lm
echo Successfully compiled function generator
Nx=200
delX=0.1
Nt=2
delT=1
./GenerateFunction $Nx $delX
echo Generated Function

gcc -I$HOME/usr/include som.c -L$HOME/usr/lib -lfftw3 -lm -o SOM
echo Successfully compiled SOM
./SOM $Nx $delX $Nt $delT
echo Executed SOM

echo Showing plots
./plot.py $Nx $delX $Nt $delT
