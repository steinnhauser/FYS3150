#!/usr/bin/env python3
import matplotlib.pyplot as plt
import numpy as np


def readfile(filename):
    """read data from one data file,
    returns list of data"""
    t = []; e = []; e_2 = []; mc = []
    cv = []; m = []; m_2 = []; acp = []
    with open(filename, 'r') as infile:
        infile.readline()
        for line in infile:
            tv,ev,e2v,mv,m2v,mcv,acpv = line.split()
            t.append(eval(tv))
            e.append(eval(ev))
            e_2.append(eval(e2v))
            m.append(eval(mv))
            m_2.append(eval(m2v))
            mc.append(eval(mcv))
            acp.append(eval(acpv))
        infile.close()
    #
    plt.plot(mc,e)
    plt.title("Energy")
    plt.show()

    plt.plot(mc, m)
    plt.title("Magnetization")
    plt.show()
    return t,e,e_2,m,m_2,mc,acp


def main():
    readfile("datafile.txt")


if __name__=='__main__':
    main()
