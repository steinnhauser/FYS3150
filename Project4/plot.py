#!/usr/bin/env python3
import matplotlib.pyplot as plt
import numpy as np


def readfile_mc(filename):
    """read data from one data file,
    returns list of data"""
    e = []; e_2 = []; mc = []
    m = []; m_2 = []; acp = []
    with open(filename, 'r') as infile:
        infile.readline()
        infile.readline()
        for line in infile:
            ev,e2v,mv,m2v,mcv,acpv = line.split()
            e.append(eval(ev))
            e_2.append(eval(e2v))
            m.append(eval(mv))
            m_2.append(eval(m2v))
            mc.append(eval(mcv))
            acp.append(eval(acpv))
        infile.close()
    return e,e_2,m,m_2,mc,acp


def readfile_avgs(filename):
    """read data from one data file,
    returns list of data"""
    t = []; e = []; m = []
    with open(filename, 'r') as infile:
        infile.readline()
        infile.readline()
        for line in infile:
            tv,ev,mv = line.split()
            t.append(eval(tv))
            e.append(eval(ev))
            m.append(eval(mv))
        infile.close()
    return t,e,m


def analytic_vals(T):
    J = 1
    k = 1
    a = 8*J/(k*T)
    E = -32*J*np.sinh(a)/(4*np.cosh(a)+12)
    EE = 256*J*np.cosh(a)/(4*np.cosh(a)+12)
    CV = (EE - E*E)/(k*T*T)
    M = (8*np.exp(a)+4)/(4*np.cosh(a)+12)
    MM = (32*np.exp(a)+8)/(4*np.cosh(a)+12)
    CHI = (MM - M*M)/(k*T)
    return E, EE, M, MM, CV, CHI


def plot_mc():
    e,e_2,m,m_2,mc,acp = readfile("datafile.txt")
    E, EE, M, MM, CV, CHI = analytic_vals(1)
    plt.plot(mc,e)
    plt.plot(mc,[E]*len(mc))
    plt.title("Energy")
    plt.show()

    plt.plot(mc, m)
    plt.plot(mc, [M]*len(mc))
    plt.title("Magnetization")
    plt.show()


def plot_avg():
    t,e,m = readfile_avgs("avg_datafile.txt")

    plt.plot(t,e, label="Average energy")
    plt.plot(t,m, label="Average magnetism")
    plt.xlabel("T")
    plt.legend()
    plt.show()


def main():






if __name__=='__main__':
    main()
