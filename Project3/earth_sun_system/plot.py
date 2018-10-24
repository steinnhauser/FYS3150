#!/usr/bin/python3
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
#plt.rc("text", usetex=True)
import numpy as np
import sys
plt.rcParams.update({'font.size': 10})

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
plt.plot([0],[0],'yo', label="Sun")
ax.plot(x, y, z, "b,", label="Earth")
ax.set_xlabel('X [AU]')
ax.set_ylabel('Y [AU]')
ax.set_zlabel('Z [AU]')
plt.legend()
plt.show()#plt.savefig("./data/" + str(fn) + "pos.pdf")

plt.figure()
plt.rcParams.update({'font.size': 15})
plt.plot(t, angm, 'g--', label='Angular momentum/mass')
plt.xlabel(r'$yr$')
plt.ylabel(r'$\frac{AU^2}{yr \cdot M_{sun}}$')
plt.grid()
plt.legend()
plt.show()#plt.savefig("./data/" + str(fn) + "ang.pdf")

plt.figure()
plt.rcParams.update({'font.size': 15})
plt.plot(t, ek, 'r--', label='kinetic energy/mass')
plt.plot(t, ep, 'b--', label='potential energy/mass')
plt.plot(t, ep+ek, 'k-', label='total energy/mass')
plt.xlabel(r'$yr$')
plt.ylabel(r'$\frac{AU^2}{yr^{2}|M_{sun}|}$')
plt.grid()
plt.legend(loc='best')
plt.show()#plt.savefig("./data/" + str(fn) + "ene.pdf")
