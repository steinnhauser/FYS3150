#!/usr/bin/env python3
import matplotlib.pyplot as plt
plt.rcParams.update({'font.size':12})
from matplotlib import animation
import numpy as np
import sys


def plot(nx,nt,dx,dt,filename):
    data = np.fromfile(filename, dtype=float).reshape((nt,nx))
    x = np.linspace(0,(nx-1)*dx,nx)
    t = np.linspace(0,(nt-1)*dt,nt)
    levels = np.linspace(0,1,101)
    plt.contourf(x,t,data,levels,cmap='jet')
    plt.colorbar()
    plt.xlabel('position [m]')
    plt.ylabel('time [s]')
    plt.show()


def main():
    # plot(101,100001,0.01,0.00001,"data/explicit.bin")
    plot(101,10001,0.01,0.0001,"data/implicit.bin")
    plot(101,10001,0.01,0.0001,"data/CrankNicolson.bin")

if __name__=="__main__":
    main()
