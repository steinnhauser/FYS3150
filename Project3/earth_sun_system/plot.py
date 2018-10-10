#!/usr/bin/python3
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import sys

fn = sys.argv[1]

with open("./data/" + str(fn) + ".txt","r") as infile:
    # first two lines
    line = infile.readline()
    title = line.split()[0]
    line = infile.readline()
    Parameters = line.split()
    x=[]; y=[]; z=[]; t=[]
    ek=[]; ep=[] # energies
    # the remaining lines with data
    for line in infile:
        xval, yval, zval, ekval, epval, tval = line.split()
        x.append(eval(xval))
        y.append(eval(yval))
        z.append(eval(zval))
        ek.append(eval(ekval))
        ep.append(eval(epval))
        t.append(eval(tval))
    infile.close()

x = np.asarray(x)
y = np.asarray(y)
z = np.asarray(z)
ek = np.asarray(ek)
ep = np.asarray(ep)
t = np.asarray(t)

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot(x, y, z, "r,", label="x")
plt.show()


plt.plot(t, ek, 'r--', label='kinetic energy')
plt.plot(t, ep, 'b--', label='potential energy')
plt.plot(t, ep+ek, 'k-', label='total energy')
plt.xlabel('time [yr]')
plt.ylabel('energy')
plt.legend()
plt.show()
