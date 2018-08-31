#!/usr/bin/python3
import matplotlib.pyplot as plt
import numpy as np


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
