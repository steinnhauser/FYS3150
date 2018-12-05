#!/usr/bin/env python3
import matplotlib.pyplot as plt
from matplotlib import animation
import numpy as np
import sys


def animate2d():
    fig = plt.figure()
    dataframes = []
    nt = 1001
    n = 101
    a = np.fromfile("data/twodimensions.bin", dtype=float).reshape((nt,n*n))
    print(len(a))
    dataframes = []
    for i in range(nt):
        im = plt.imshow(a[i,:].reshape((n,n)))
        dataframes.append(im)
    
    ani = animation.FuncAnimation(fig, dataframes, interval=20, blit=True)

    plt.show()

if __name__=='__main__':
    animate2d()
