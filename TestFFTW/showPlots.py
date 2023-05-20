#!/bin/python3
import matplotlib.pyplot as plt

def main():
    inputFile = open("data.csv", "r")
    input = inputFile.readlines()
    x, y = [], []
    for inputElement in input:
        xi, yi = inputElement.split(",")
        x.append(float(xi))
        y.append(float(yi))

    plt.plot(x,y)
    plt.show()

    outputFile = open("transformData.csv", "r")
    output = outputFile.readlines()
    x, y = [], []
    for outputElement in output:
        xi, yi = outputElement.split(",")
        x.append(float(xi))
        y.append(float(yi))

    plt.plot(x,y)
    plt.show()
    return

main()
