#!/usr/bin/env python3
import matplotlib.pyplot as plt
import matplotlib.animation as animation
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
    infile = open("data/twodimensions.txt", "r")
    n = eval(infile.readline()) + 1
    nt = eval(infile.readline()) + 1
    a = np.fromfile("data/twodimensions.bin", dtype=float).reshape((nt,n*n))
    imagelist = []
    dt = 0.001
    for i in range(nt):
        imagelist.append(a[i].reshape((n,n)))

    im = plt.imshow(imagelist[0], animated=True)

    def updatefig(j):
        im.set_array(imagelist[j])
        return [im]

    ani = animation.FuncAnimation(fig, updatefig, frames=range(nt),
                interval=50, blit=True)

    plt.colorbar()
    # ani.save("ani.mp4")
    plt.show()


if __name__=='__main__':
    animate2d()
