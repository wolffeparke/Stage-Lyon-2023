#!/bin/python3
import matplotlib.pyplot as plt
import math

def main():
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
    for outputElement in output:
        xi, yReali, yImagi = map(float,outputElement.split(","))
        x.append(xi)
        yReal.append(yReali)
        yImag.append(yImagi)
        yMag.append(math.sqrt(yReali**2+yImagi**2))

    plt.plot(x,yReal,'b', label="Re(F(k))")
    plt.plot(x,yImag,'r', label="Im(F(k))")
    plt.plot(x,yMag,'g', label="|F(k)|^2")
    plt.legend()
    plt.show()
    return

main()
