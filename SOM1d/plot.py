#!/bin/python3
import matplotlib.pyplot as plt
import math
import sys

def main():
    Nx = int(sys.argv[1])
    delX = float(sys.argv[2])
    Nt = int(sys.argv[3])
    delT = float(sys.argv[4])
    inputFile = open("psi.txt", "r")
    inputLines = inputFile.readlines()

    x, yRe, yIm = [], [], []
    for i in range(Nx+1):
        xi, yRei, yImi = inputLines[i].split(",")
        x.append(float(xi))
        yRe.append(float(yRei))
        yIm.append(float(yImi))

    plt.plot(x,yRe,"b", label="Re")
    plt.plot(x,yIm,"r", label="Im")
    plt.show()

    x, yRe, yIm = [], [], []
    for i in range(Nx+1, 2*Nx+1, 1):
        xi, yRei, yImi = inputLines[i].split(",")
        x.append(float(xi))
        yRe.append(float(yRei))
        yIm.append(float(yImi))

    plt.plot(x,yRe,"b", label="Re")
    plt.plot(x,yIm,"r", label="Im")
    plt.show()

    x, yRe, yIm = [], [], []
    for i in range(2*Nx+1, 3*Nx+1, 1):
        xi, yRei, yImi = inputLines[i].split(",")
        x.append(float(xi))
        yRe.append(float(yRei))
        yIm.append(float(yImi))

    plt.plot(x,yRe,"b", label="Re")
    plt.plot(x,yIm,"r", label="Im")
    plt.show()

    x, yRe, yIm = [], [], []
    for i in range(3*Nx+1, 4*Nx+1, 1):
        xi, yRei, yImi = inputLines[i].split(",")
        x.append(float(xi))
        yRe.append(float(yRei))
        yIm.append(float(yImi))

    plt.plot(x,yRe,"b", label="Re")
    plt.plot(x,yIm,"r", label="Im")
    plt.show()

    x, yRe, yIm = [], [], []
    for i in range(4*Nx+1, 5*Nx+1, 1):
        xi, yRei, yImi = inputLines[i].split(",")
        x.append(float(xi))
        yRe.append(float(yRei))
        yIm.append(float(yImi))

    plt.plot(x,yRe,"b", label="Re")
    plt.plot(x,yIm,"r", label="Im")
    plt.show()

    x, yRe, yIm = [], [], []
    for i in range(5*Nx+1, 6*Nx+1, 1):
        xi, yRei, yImi = inputLines[i].split(",")
        x.append(float(xi))
        yRe.append(float(yRei))
        yIm.append(float(yImi))

    plt.plot(x,yRe,"b", label="Re")
    plt.plot(x,yIm,"r", label="Im")
    plt.show()

main()
