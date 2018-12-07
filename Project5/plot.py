#!/usr/bin/env python3
import matplotlib.pyplot as plt
plt.rcParams.update({'font.size':12})
from matplotlib import animation
import numpy as np
import sys


def plot(params,exp_params,folder,time,title):
    plt.figure()
    plt.title(title)
    files = ["im","cn","an"]
    labels = ["Implicit scheme","Crank-Nicolson scheme","Analytic solution"]

    # explicit plot
    nxe,nte,dxe,dte = exp_params
    xe = np.linspace(0,nxe*dxe,nxe+1)
    data = np.fromfile("data/"+folder+"ex.bin", dtype=float).reshape((nte+1,nxe+1))
    plt.plot(xe,data[int(time*nte)],label="Explicit scheme")

    # implicit, Crank-Nicolson and analytic solution plot
    nx,nt,dx,dt = params
    x = np.linspace(0,nx*dx,nx+1)
    for file,l in zip(files,labels):
        data = np.fromfile("data/"+folder+file+".bin", dtype=float).reshape((nt+1,nx+1))
        plt.plot(x,data[int(time*nt)],label=l)

    plt.legend()
    plt.xlabel('Position [ ]')
    plt.ylabel('Temperature [ ]')
    plt.grid()
    plt.show()


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


if __name__=="__main__":
    for time in [0.1,0.5]:
        params = [10,1000,0.1,0.001]
        exp_params = params
        plot(params,exp_params,"dx01/",time,r"$\Delta x = 0.1$, time = %1.1f s" % time)
        params = [100,1000,0.01,0.001]
        exp_params = [100,100000,0.01,0.00001]
        plot(params,exp_params,"dx001/",time,r"$\Delta x = 0.01$, time = %1.1f s" % time)
