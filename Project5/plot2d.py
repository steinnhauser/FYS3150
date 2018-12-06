#!/usr/bin/env python3
import matplotlib.pyplot as plt
from matplotlib import animation
import numpy as np
import sys


def plot(time):
    fig = plt.figure()
    dataframes = []

    infile = open("data/twodimensions.txt", "r")
    n = eval(infile.readline()) + 1
    nt = eval(infile.readline()) + 1
    a = np.fromfile("data/twodimensions.bin", dtype=float).reshape((nt,n*n))
    dataframes = []
    plt.imshow(dataframes[nt-1])
    plt.colorbar()
    plt.show()


def animate2d():
    fig = plt.figure()
    dataframes = []

    infile = open("data/twodimensions.txt", "r")
    n = eval(infile.readline()) + 1
    nt = eval(infile.readline()) + 1

    a = np.fromfile("data/twodimensions.bin", dtype=float).reshape((nt,n*n))
    dataframes = []

    for i in range(nt):
        dataframes.append(a[i,:].reshape((n,n)))

    # for i in range(nt):
        # im = plt.imshow(a[i,:].reshape((n,n)), animated=True)
        # dataframes.append(im)

    # ani = animation.ArtistAnimation(fig, dataframes, interval=20, blit=True)
    plt.imshow(dataframes[nt-1])
    plt.colorbar()
    plt.show()


if __name__=='__main__':
    animate2d()
