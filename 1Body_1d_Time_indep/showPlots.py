#!/bin/python3
import matplotlib.pyplot as plt

def main():
    inputFile = open("phi.txt", "r")
    input = inputFile.readlines()
    x, yReal, yImag, yMag = [], [], [], []
    for inputElement in input:
        xi, yReali, yImagi = map(float,inputElement.split(","))
        x.append(xi)
        yReal.append(yReali)
        yImag.append(yImagi)
        yMag.append(yReali**2+yImagi**2)

    plt.plot(x,yReal, label="Re(phi)")
    plt.plot(x, yImag, 'r', label="Im(phi)")
    plt.plot(x, yMag, 'g', label="|phi|^2")
    plt.legend()
    plt.show()

main()
