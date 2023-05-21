#!/bin/bash
N=100

gcc -g3 -o Numerov -lm numerov.c
./Numerov $N
./showPlots.py
