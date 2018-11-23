#!/usr/bin/env python3
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import sys

def plotfunc(filename):
    a = pd.read_csv(filename, header=None)
    plt.plot(a)
    # plt.axis([0,100,-100,100])
    plt.show()
    #infile = open(filename,"r")




def main():
    if str(sys.argv[1])=="ex":
        fn = "data/explicitTest.csv"
    elif str(sys.argv[1])=="im":
        fn = "data/implicitTest.csv"
    plotfunc(fn)


if __name__=="__main__":
    main()
