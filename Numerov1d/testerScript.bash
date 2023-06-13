#!/bin/bash
N=300

gcc -g3 -o Numerov numerov.c -lm
./Numerov $N
./showPlots.py
