#!/usr/bin/python3
import matplotlib.pyplot as plt
import numpy as np
import re

rho = []
psi = []
with open("project2.txt","r") as infile:
    line = infile.readline()
    words = re.sub(":,[^\w]", " ",  line).split()
    eigval = eval(words[1])
    infile.readline()
    for line in infile:
        r,p = line.split()
        rho.append(eval(r))
        psi.append(eval(p))
    infile.close()

psi = np.asarray(psi)
psi *= psi
plt.title(r"$\lambda = %f$" % eigval)
plt.plot(rho,psi)
plt.xlabel(r"$\rho$")
plt.ylabel(r"$|\psi|^2$")
plt.grid()
plt.show()
