#!/usr/bin/env python3
import matplotlib.pyplot as plt
from matplotlib import animation
import numpy as np
import pandas as pd
import sys

def plotfunc(filename):
    a = pd.read_csv(filename, header=None)
    plt.plot(a)
    # plt.axis([0,100,-100,100])
    plt.show()
    #infile = open(filename,"r")


def animatefunc(filename):
    data = np.zeros((101,101))
    with open(filename) as infile:
        for x,line in enumerate(infile):
            for y,val in enumerate(line.split(',')):
                data[x,y] = eval(val)
        infile.close()
    fig = plt.figure()
    ax = plt.axes(xlim=(0, 1), ylim=(0, 1))
    line, = ax.plot([], [], lw=2)

    # initialization function: plot the background of each frame
    def init():
        line.set_data([], [])
        return line,

    # animation function.  This is called sequentially
    def animate(i):
        x = np.linspace(0,1,101)
        y = data[i,:]
        line.set_data(x, y)
        return line,

    # call the animator.  blit=True means only re-draw the parts that have changed.
    anim = animation.FuncAnimation(fig, animate, init_func=init,
                                   frames=101, interval=20, blit=False)
    plt.show()


def main():
    if len(sys.argv) < 2:
        print("give command line argument of which file to plot: ex, im or CN")
        sys.exit(1)

    if str(sys.argv[1])=="ex":
        fn = "data/explicitTest.csv"
    elif str(sys.argv[1])=="im":
        fn = "data/implicitTest.csv"
    elif str(sys.argv[1])=="CN":
        fn = "data/CrankNicolsonTest.csv"

    answer = str(input("Would you like to animate? (Y/N) "))
    if answer == "Y" or answer == "y":
        animatefunc(fn)
    elif answer == "N" or answer == "n":
        plotfunc(fn)


if __name__=="__main__":
    main()
