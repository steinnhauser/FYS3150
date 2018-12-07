#!/usr/bin/env python3
import matplotlib.pyplot as plt
plt.rcParams.update({'font.size':12})
from matplotlib import animation
import numpy as np
import sys


def plot(params,folder):
    times = [0.1,0.2]
    dx = params[2]
    plt.figure()
    plt.title(r"$\Delta x = %1.2f$" % dx)
    for time in times:
        files = ["ex","im","cn","an"]
        labels = ["Explicit scheme",
                  "Implicit scheme",
                  "Crank-Nicolson scheme",
                  "Analytic solution"
                  ]
        arrays = []
        errors = []
        nx,nt,dx,dt = params
        x = np.linspace(0,nx*dx,nx+1)

        # implicit, Crank-Nicolson and analytic solution plot
        for file,l in zip(files,labels):
            data = np.fromfile("data/"+folder+file+".bin", dtype=float).reshape((nt+1,nx+1))
            arr = data[int(time*nt)]
            arrays.append(arr)
            plt.plot(x,arr,label=l+", time=%1.2f" % time)

    plt.legend()
    plt.ylabel('Temperature [ ]')
    plt.grid()

    # Error analysis
    for time in times:
        plt.figure()
        plt.title(r"$\Delta x = %1.2f$, time=%1.2f" % (dx,time))
        labels = ["Explicit scheme","Implicit scheme","Crank-Nicolson scheme"]
        for i,l in enumerate(labels):
            err = np.abs(arrays[i] - arrays[3])
            plt.plot(x,err,label=l)

        plt.legend()
        plt.xlabel('Position [ ]')
        plt.ylabel('Absolute error [ ]')
        plt.yscale('log')
        plt.grid()


if __name__=="__main__":
    # dx = 0.1
    # params = [10,1000,0.1,0.001]
    # plot(params,"dx01/")
    # dx = 0.01
    params = [100,100000,0.01,0.00001]
    plot(params,"dx001/")
    plt.show()
