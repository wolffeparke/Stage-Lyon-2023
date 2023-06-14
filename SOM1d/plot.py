#!/bin/python3
import matplotlib.pyplot as plt
import math
import sys
import string

def main():
    Nx = int(sys.argv[1])
    delX = float(sys.argv[2])
    Nt = int(sys.argv[3])
    delT = float(sys.argv[4])
    inputFile = open("psi.txt", "r")
    inputLines = inputFile.readlines()
    vFile = open("Vx.txt", "r")
    vLines = vFile.readlines()

    for t in range(Nt+1):
        V, x, yRe, yIm, yMag = [], [], [], [], []
        for i in range(t*Nx+1,(t+1)*Nx+1,1):
            xi, yRei, yImi = inputLines[i].split(",")
            x.append(float(xi))
            yRe.append(float(yRei))
            yIm.append(float(yImi))
            yMag.append(float(yRei)**2+float(yImi)**2)
            V.append(float(vLines[i-(t*Nx+1)]))

        plt.plot(x,yRe,"b", label="Re")
        plt.plot(x,yIm,"r", label="Im")
        #plt.plot(x,yMag,"g", label="Mag")
        plt.plot(x,V,"orange", label="V(x)")
        plt.legend()
        ax = plt.gca()
        ax.set_ylim([-2,2])
        plt.savefig("animationFrames/t{}.png".format(t))
        plt.clf()

main()
