#!/bin/bash
rm psi.txt
rm -r animationFrames
mkdir animationFrames
rm SOM.gif
gcc -o GenerateFunction generateFunction.c -lm
echo Successfully compiled function generator
Nx=200
delX=0.1
Nt=400
delT=0.6
./GenerateFunction $Nx $delX
echo Generated Function

gcc -I$HOME/usr/include som.c -L$HOME/usr/lib -lfftw3 -lm -o SOM
echo Successfully compiled SOM
./SOM $Nx $delX $Nt $delT
echo Executed SOM

echo Computing plots
gnuplot -c "gnuScript.gp" $Nx $Nt

echo Compiling gif
convert -dispose previous -delay 5 -loop 0 `ls -v animationFrames/t*.png` SOM.gif
echo Showing gif
animate SOM.gif
