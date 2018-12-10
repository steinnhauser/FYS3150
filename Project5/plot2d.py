#!/usr/bin/env python3
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from mpl_toolkits.mplot3d import Axes3D
plt.rcParams.update({'font.size':12})
import numpy as np
import sys


def plot(time):
    infile = open("data/twodimensions.txt", "r")
    n = eval(infile.readline()) + 1
    nt = eval(infile.readline()) + 1
    imagelist = []
    dt = 0.0001
    for i in range(1,nt):
        image = np.fromfile("data/images/u" + str(i) + ".bin", dtype=float)
        imagelist.append(image.reshape((n,n)))

    ti = int(time/dt) - 1
    x = np.linspace(0,1,n)
    y = np.linspace(0,1,n)
    X,Y = np.meshgrid(x,y)
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    ax.plot_surface(X,Y,imagelist[ti],cmap='RdBu_r')
    ax.set_xlabel('x')
    ax.set_ylabel('y')
    ax.set_zlabel('Temperature, [ ]')
    # ax.set_title('Numerical solution at t=%1.1f' % time)

    fig = plt.figure()
    Z = np.exp(-2*np.pi**2*time)*np.sin(np.pi*X)*np.sin(np.pi*Y)
    ax = fig.add_subplot(111, projection='3d')
    ax.plot_surface(X,Y,Z,cmap='PRGn')
    ax.set_xlabel('x')
    ax.set_ylabel('y')
    ax.set_zlabel('Temperature, [ ]')
    # ax.set_title('Analytic solution at t=%1.1f' % time)
    # plt.show()


def plot_error_dt():
    files = [
            "twodim_dx001_dt00001/u",
            "twodim_dx001_dt0001/u",
            "twodim_dx001_dt001/u"
            ]
    ntlist = [2000,200,20]
    dtlist = [0.0001,0.001,0.01]
    n = 101
    dx = 0.01
    lablelist = ["0.0001","0.001","0.01"]

    plt.figure()
    for file,nt,dt,lab in zip(files,ntlist,dtlist,lablelist):
        imagelist = []
        for i in range(1,nt):
            image = np.fromfile("data/" + file + str(i) + ".bin", dtype=float)
            imagelist.append(image.reshape((n,n)))
        t = np.linspace(0,dt*(nt-1),nt-1)
        error = np.zeros(nt-1)
        mid = int((n-1)/2)
        for i in range(nt-1):
            image =  imagelist[i]
            numerical = image[mid,mid]
            analytic = np.exp(-2*np.pi**2*dt*i)
            error[i] = np.abs((numerical-analytic)) #/analytic
        plt.plot(t,error,label=r"$\Delta t=$" + lab)
    plt.title(r"$\Delta x=0.01$")
    plt.xlabel("Time, [s]")
    plt.yscale('log')
    plt.grid()
    plt.legend()
    plt.ylabel("Error, [ ]")
    plt.show()


def plot_error_dx():
    files = [
            "twodim_dx01_dt001/u",
            "twodim_dx001_dt001/u",
            "twodim_dx0001_dt001/u",
            ]
    nxlist = [11,101,1001]
    dxlist = [0.1,0.01,0.001]
    nt = 21
    dt = 0.01
    lablelist = ["0.1","0.01","0.001"]

    plt.figure()
    for file,n,dx,lab in zip(files,nxlist,dxlist,lablelist):
        imagelist = []
        for i in range(1,nt):
            image = np.fromfile("data/" + file + str(i) + ".bin", dtype=float)
            imagelist.append(image.reshape((n,n)))
        t = np.linspace(0,dt*(nt-1),nt-1)
        error = np.zeros(nt-1)
        mid = int((n-1)/2)
        for i in range(nt-1):
            image =  imagelist[i]
            numerical = image[mid,mid]
            analytic = np.exp(-2*np.pi**2*dt*i)
            error[i] = np.abs((numerical-analytic)) #/analytic
        plt.plot(t,error,label=r"$\Delta x=$"+lab)
    plt.title(r"$\Delta t=0.01$")
    plt.xlabel("Time, [s]")
    plt.yscale('log')
    plt.grid()
    plt.legend()
    plt.ylabel("Error, [ ]")
    plt.show()


def animate2d():
    fig = plt.figure()
    infile = open("data/twodimensions.txt", "r")
    n = eval(infile.readline()) + 1
    nt = eval(infile.readline()) + 1
    imagelist = []
    dt = 0.001
    for i in range(1,nt,10):
        image = np.fromfile("data/images/u" + str(i) + ".bin", dtype=float)
        imagelist.append(image.reshape((n,n)))

    im = plt.imshow(imagelist[0], animated=True)

    def updatefig(j):
        im.set_array(imagelist[j])
        return [im]

    ani = animation.FuncAnimation(fig, updatefig, frames=range(len(imagelist)),
        interval=50, blit=True)

    plt.colorbar()
    plt.xlabel('x')
    plt.ylabel('y')
    ani.save('twodim.gif', writer='imagemagick', fps=30)


if __name__=='__main__':
    # animate2d()
    # plot(0.1)
    plot_error_dt()
    plot_error_dx()
