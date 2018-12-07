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
    plt.figure()
    plt.contourf(x,t,data,levels,cmap='jet')
    plt.colorbar()
    plt.xlabel('position [m]')
    plt.ylabel('time [s]')



def errorplot():
    nx = 100
    dx = 0.01
    x = np.linspace(0,1,nx+1)
    # analytic
    nta = 100
    dta = 0.01
    # numericial
    ntn = 100000
    dtn = 0.00001
    analytic = np.fromfile("data/analyticsol1D.bin", dtype=float).reshape((nta+1,nx+1))
    numerical = np.fromfile("data/explicit.bin", dtype=float).reshape((ntn+1,nx+1))
    # time 0.1 s:
    ta1 = int(0.1*nta)
    tn1 = int(0.1*ntn)
    analytic_time01 = analytic[ta1]
    numerical_time01 = numerical[tn1]
    error_time1 = np.abs(analytic_time01-numerical_time01)
    plt.plot(x,error_time1)
    plt.show()


def main():
    # "data/analyticsol1D.bin"
    # plot(101,100001,0.01,0.00001,"data/explicit.bin")
    # plot(1001,101,0.001,0.01,"data/analyticsol1D.bin")
    # plot(101,10001,0.01,0.0001,"data/implicit.bin")
    # plot(101,10001,0.01,0.0001,"data/CrankNicolson.bin")
    errorplot()
    # plt.show()


if __name__=="__main__":
    main()
