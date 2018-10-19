#!/usr/bin/python3
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
#plt.rc("text", usetex=True)
import numpy as np
import sys

if len(sys.argv)!=2:
    print("Bad usage: Input name of data file as argument.")
    exit(1)
else:
    fn = sys.argv[1]

with open("./data/" + str(fn) + ".txt","r") as infile:
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

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot(x, y, z, "r,", label="x")
plt.show()

plt.plot(t, angm, 'r--', label='Angular momentum/mass')
plt.xlabel(r'$yr$')
plt.ylabel(r'$AU^2 yr^{-1} M_{sun}^{-1}$')
plt.grid()
plt.legend()
plt.show()


plt.plot(t, ek, 'r--', label='kinetic energy/mass')
plt.plot(t, ep, 'b--', label='potential energy/mass')
plt.plot(t, ep+ek, 'k-', label='total energy/mass')
plt.xlabel(r'$yr$')
plt.ylabel(r'$AU^2 yr^{-2}$')
plt.grid()
plt.legend()
plt.show()
