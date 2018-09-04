#!/usr/bin/python3
import matplotlib.pyplot as plt
import numpy as np
import sys

exponent = int(sys.argv[1])

maxerrors = []
h_list = []

for i in range(1, exponent+1):
	n = int(10**i)
	h = 1./(n+1)
	infile = open("results%i.txt" % n, "r")
	steps = [0]
	exact = [0]
	comp  = [0]
	err   = []
	for line in infile:
		a, b, c, d = line.split()
		steps.append(eval(a))
		exact.append(eval(b))
		comp.append(eval(c))
		err.append(eval(d))
	steps.append(1)
	exact.append(0)
	comp.append(0)

	maxerrors.append(max(err))
	h_list.append(h)
	'''
	plt.plot(steps, exact, "r.", label="Analytical solution")
	plt.plot(steps, comp, "b.", label="Numerical solution")
	plt.title("Analytical vs Numerical solution for $n=%i$" %n)
	plt.legend(loc="best")
	plt.show()
	'''

plt.plot(h_list, maxerrors, "ro")
plt.title("Max errors as a function of the step length.")
plt.show()

print(maxerrors)

h_arr = np.asarray(h_list)
me_arr = abs(np.asarray(maxerrors))

print(h_arr, me_arr)

lg_a = np.log10(h_arr)
lg_m = np.log10(me_arr)

plt.plot(lg_a, lg_m)
plt.show()



"""
infile=open("results10.txt", "r")
stepsize1=[]
exactsol=[]
compsol=[]
err1=[]
for line in infile:
	a = line.split()
	stepsize1.append(float(a[0]))
	exactsol.append(float(a[1]))
	compsol.append(float(a[2]))
	err1.append(float(a[3]))
infile.close()
plt.plot(stepsize1, exactsol, "r.", label="Analytical solution")
plt.plot(stepsize1, compsol, "b.", label="Numerical solution")
plt.title("Analytical vs Numerical solution for $n=10$")
plt.legend(loc="best")
plt.show()


infile=open("results1000.txt", "r")
stepsize2=[]
exactsol=[]
compsol=[]
err2=[]
for line in infile:
	a = line.split()
	stepsize2.append(float(a[0]))
	exactsol.append(float(a[1]))
	compsol.append(float(a[2]))
	err2.append(float(a[3]))
infile.close()
plt.plot(stepsize2, exactsol, "r.", label="Analytical solution")
plt.plot(stepsize2, compsol, "b.", label="Numerical solution")
plt.title("Analytic vs Numeric solution for $n=100$")
plt.legend(loc="best")
plt.show()



infile=open("results1000.txt", "r")
stepsize3=[]
exactsol=[]
compsol=[]
err3=[]
for line in infile:
	a = line.split()
	stepsize3.append(float(a[0]))
	exactsol.append(float(a[1]))
	compsol.append(float(a[2]))
	err3.append(float(a[3]))
infile.close()
plt.plot(stepsize3, exactsol, "r.", label="Analitical solution")
plt.plot(stepsize3, compsol, "b.", label="Numerical solution")
plt.title("Analytic vs Numeric solution for $n=1000$")
plt.legend(loc="best")
plt.show()


plt.plot(stepsize1, err1, label="Error for $n=10$")
plt.plot(stepsize2, err2, label="Error for $n=100$")
plt.plot(stepsize3, err3, label="Error for $n=1000$")
plt.title("Absolute errors of the numerical calculations.")
plt.legend(loc="best")
plt.show()
"""
