#!/usr/bin/env python3
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from mpl_toolkits.mplot3d import Axes3D
plt.rcParams.update({'font.size':12})
import numpy as np
import sys


def plot(time):
    infile = open("data/twodimensions.txt", "r")
    n = 1001#eval(infile.readline()) + 1
    nt = 21#eval(infile.readline()) + 1
    imagelist = []
    dt = 0.001
    for i in range(1,nt):
        image = np.fromfile("data/twodim_dx0001_dt0001/u" + str(i) + ".bin", dtype=float)
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
    plt.show()


def animate2d():
    fig = plt.figure()
    nx = 151
    ny = 121
    nt = 10000
    imagelist = []
    dt = 0.0001
    for i in range(1,nt,100):
        image = np.fromfile("data/lithosphere/u" + str(i) + ".bin", dtype=float)
        imagelist.append(image.reshape((ny,nx)))

    im = plt.imshow(imagelist[0], animated=True)

    def updatefig(j):
        im.set_array(imagelist[j])
        return [im]

    ani = animation.FuncAnimation(fig, updatefig, frames=range(len(imagelist)),
        interval=50, blit=True)

    plt.colorbar()
    plt.xlabel(r'$n_x$')
    plt.ylabel(r'$n_y$')
    ani.save('litho.gif', writer='imagemagick', fps=30)


if __name__=='__main__':
    animate2d()
