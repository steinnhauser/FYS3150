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
        "data/lithosphere_QR_equilfirst_noDecay.bin"
        ]
    labels = ["Numerical: no heat",
        "Numerical: natural heat",
        "Numerical: subduction"
        ]
    colors = ['b-','y-','r-']
    numerical = []
    nx = 126
    ny = 101
    nt = 100
    for file,label,c in zip(files,labels,colors):
        image = np.fromfile(file, dtype=float).reshape((ny,nx))
        temp = image[:,int(nx/2)]*1292 + 8
        numerical.append(temp)
        depth = np.linspace(0,120,ny)
        plt.plot(depth,temp,c,label=label)
    plt.xlabel("Depth [km]")
    plt.ylabel(r"Temperature $[^\circ C]$")
    plt.grid()

    # analytic: no heat production
    analytic = []
    x = np.linspace(0,120,101)
    y = np.linspace(0,1,101)*1292 + 8
    analytic.append(y)
    plt.plot(x,y,'b--',label="Analytic: no heat")

    # analytic: natural heat production
    xzones = [x[:17],x[17:34],x[34:]]
    zones = [
        [-0.28,-23.66,8],
        [-0.07,-15.26,92],
        [-0.01,-10.46,188]
        ]
    y2 = []
    for x,zone in zip(xzones,zones):
        y = np.polyval(zone,-x)
        y2.append(y)
        plt.plot(x,y,'y--',label="Analytic: natural heat")
    analytic.append(np.concatenate((y2[0],y2[1],y2[2])))
    # analytic: natural + subduction
    zones = [
        [-0.28,-29,8],
        [-0.07,-20.6,92],
        [-0.11,-23.8,28]
        ]
    y3 = []
    for x,zone in zip(xzones,zones):
        y = np.polyval(zone,-x)
        y3.append(y)
        plt.plot(x,y,'r--',label="Analytic: subduction")
    analytic.append(np.concatenate((y3[0],y3[1],y3[2])))
    plt.legend()
    plt.show()

    # error plot
    labels = ["Error: no heat",
        "Error: natural heat",
        "Error: subduction"
        ]
    x = np.linspace(0,120,101)
    for a,n,lab in zip(analytic,numerical,labels):
        plt.plot(x[1:-1],np.abs(a[1:-1]-n[1:-1])/a[1:-1],label=lab)
    plt.yscale('log')
    plt.xlabel('Depth [km]')
    plt.ylabel('Relative error')
    plt.grid()
    plt.legend()
    plt.show()


if __name__=='__main__':
    plot()
