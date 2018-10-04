#!/usr/bin/python3
import matplotlib.pyplot as plt
import numpy as np
import sys

fn=sys.argv[1]

with open("./Data/" + str(fn) + ".txt","r") as infile:
    # first three lines
    line = infile.readline()
    Title=line.split()[0]

    line = infile.readline()
    Parameters = line.split()

    x=[]
    y=[]
    z=[]
    t=[]

    infile.readline()
    for line in infile:
        xval, yval, zval, tval = line.split()
        x.append(xval)
        y.append(yval)
        z.append(zval)
        t.append(tval)
    infile.close()

plt.plot(t, x, "r--", label="x")
plt.plot(t, y, "r--", label="x")
plt.plot(t, z, "r--", label="x")
plt.show()
