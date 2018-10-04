#!/usr/bin/python3
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import sys

fn = sys.argv[1]

with open("./data/" + str(fn) + ".txt","r") as infile:
    # first three lines
    line = infile.readline()
    title = line.split()[0]
    line = infile.readline()
    Parameters = line.split()
    x=[]; y=[]; z=[]; t=[]
    for line in infile:
        xval, yval, zval, tval = line.split()
        x.append(eval(xval))
        y.append(eval(yval))
        z.append(eval(zval))
        t.append(eval(tval))
    infile.close()

x = np.asarray(x)
y = np.asarray(y)
z = np.asarray(z)

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

ax.plot(x, y, z, "r--", label="x")
#plt.plot(t, y, "r--", label="x")
#plt.plot(t, z, "r--", label="x")
plt.show()
