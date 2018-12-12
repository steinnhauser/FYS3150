#!/usr/bin/env python3
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from mpl_toolkits.mplot3d import Axes3D
plt.rcParams.update({'font.size':15})
import numpy as np
import sys


def plot():
    files = [
        "data/lithosphere.bin",
        "data/lithosphere_Q.bin",
        "data/lithosphere_QR1.bin"
        ]
    labels = ["Numerical: Q=0",
        "Numerical: Q",
        "Numerical: Q + subduction"
        ]
    colors = ['b-','y-','r-']
    nx = 126
    ny = 101
    nt = 100
    for file,label,c in zip(files,labels,colors):
        image = np.fromfile(file, dtype=float).reshape((ny,nx))
        temp = image[:,int(nx/2)]*1292 + 8
        depth = np.linspace(0,120,ny)
        plt.plot(depth,temp,c,label=label)
    plt.xlabel("Depth [km]")
    plt.ylabel(r"Temperature $[^\circ C]$")
    plt.grid()

    # analytic: no heat production
    x = np.linspace(0,120,121)
    y = np.linspace(0,1,121)*1292 + 8
    plt.plot(x,y,'b--',label="Analytic: Q=0")

    # analytic: natural heat production
    xzones = [np.linspace(0,20,21),
        np.linspace(20,40,21),
        np.linspace(40,120,100)
        ]
    zones = [
        [-0.28,-23.66,8],
        [-0.07,-15.26,92],
        [-0.01,-10.46,188]
        ]
    for x,zone in zip(xzones,zones):
        y = np.polyval(zone,-x)
        plt.plot(x,y,'y--',label="Analytic: Q")
    # analytic: natural + subduction
    xzones = [np.linspace(0,20,100),
        np.linspace(20,40,100),
        np.linspace(40,120,100)
        ]
    zones = [
        [-0.28,-29,8],
        [-0.07,-20.6,92],
        [-0.11,-23.8,28]
        ]
    for x,zone in zip(xzones,zones):
        y = np.polyval(zone,-x)
        plt.plot(x,y,'r--',label="Analytic: Q + subduction")

    plt.legend()
    plt.show()


if __name__=='__main__':
    plot()
