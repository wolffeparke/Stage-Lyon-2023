#!/bin/python3
import matplotlib.pyplot as plt
import math
import sys

def main():
    N = int(sys.argv[1])

    print("Processing initial function plot")

    inputFile = open("data.csv", "r")
    inputLines = inputFile.readlines()
    x, y = [], []
    for inputElement in inputLines:
        xi, yi = inputElement.split(",")
        x.append(float(xi))
        y.append(float(yi))

    plt.plot(x,y)
    plt.show()

    outputFile = open("transformData.csv", "r")
    output = outputFile.readlines()
    x, yReal, yImag, yMag = [], [], [], []
    for i in range(N):
        outputElement = output[i]
        xi, yReali, yImagi = map(float,outputElement.split(","))
        x.append(xi)
        yReal.append(yReali)
        yImag.append(yImagi)
        yMag.append(math.sqrt(yReali**2+yImagi**2))

    plt.plot(x,yReal,'b', label="Re(F(k))")
    plt.plot(x,yImag,'r', label="Im(F(k))")
    plt.legend()
    plt.show()
    
    x, yReal, yImag, yMag = [], [], [], []
    for i in range(N, 2*N, 1):
        outputElement = output[i]
        xi, yReali, yImagi = map(float,outputElement.split(","))
        x.append(xi)
        yReal.append(yReali)
        yImag.append(yImagi)
        yMag.append(math.sqrt(yReali**2+yImagi**2))

    plt.plot(x,yReal,'b', label="Re(F(k))")
    plt.plot(x,yImag,'r', label="Im(F(k))")
    plt.legend()
    plt.show()
    return

main()
