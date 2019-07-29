#!/usr/bin/python3
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import sys

if len(sys.argv)!=2:
    print("Bad usage: Input name of data file as argument.")
    exit(1)
else:
    fn = sys.argv[1]


def readfile(filename):
    with open("./data/" + str(filename) + ".txt","r") as infile:
        # first two lines
        line = infile.readline()
        title = line.split()[0]
        line = infile.readline()
        Parameters = line.split()
        x=[]; y=[]; z=[]; t=[]
        ek=[]; ep=[]; angm=[] # energies
        # the remaining lines with data
        for line in infile:
            xval, yval, zval, ekval, epval, angval, tval = line.split()
            x.append(eval(xval))
            y.append(eval(yval))
            z.append(eval(zval))
            ek.append(eval(ekval))
            ep.append(eval(epval))
            angm.append(eval(angval))
            t.append(eval(tval))
        infile.close()

    x = np.asarray(x)
    y = np.asarray(y)
    z = np.asarray(z)
    ek = np.asarray(ek)
    ep = np.asarray(ep)
    angm = np.asarray(angm)
    t = np.asarray(t)
    return x,y,z,ek,ep,angm,t


def plot_position(x,y,z):
    fig = plt.figure()
    plt.rcParams.update({'font.size': 15})
    ax = fig.add_subplot(111, projection='3d')
    plt.plot([0],[0],'yo', label="Sun")
    ax.plot(x, y, z, "b,", label="Earth")
    ax.set_xlabel('X [AU]')
    ax.set_ylabel('Y [AU]')
    ax.set_zlabel('Z [AU]')
    plt.legend()
    plt.show()


def plot_ang_mom(angm,t):
    plt.figure()
    plt.rcParams.update({'font.size': 15})
    plt.plot(t, angm, 'g--', label='Angular momentum/mass')
    plt.xlabel(r'$yr$')
    plt.ylabel(r'$\frac{AU^2}{yr \cdot M_{sun}}$')
    plt.grid()
    plt.legend()
    plt.show()


def plot_energy(ek,ep,t):
    plt.figure()
    plt.rcParams.update({'font.size': 15})
    plt.plot(t, ek, 'r--', label='kinetic energy/mass')
    plt.plot(t, ep, 'b--', label='potential energy/mass')
    plt.plot(t, ep+ek, 'k-', label='total energy/mass')
    plt.xlabel(r'$yr$')
    plt.ylabel(r'$\frac{AU^2}{yr^{2}|M_{sun}|}$')
    plt.grid()
    plt.legend(loc='best')
    plt.show()


if __name__=='__main__':
    x,y,z,ek,ep,angm,t = readfile(fn)
    plot_position(x,y,z)
    plot_ang_mom(angm,t)
    plot_energy(ek,ep,t)
