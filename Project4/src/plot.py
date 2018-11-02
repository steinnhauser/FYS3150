#!/usr/bin/env python3
import matplotlib.pyplot as plt
import numpy as np


def readfile(filename):
    """read data from one data file,
    returns list of data"""
    t = []; e = []; e_2 = []; mc = []
    cv = []; m = []; m_2 = []; acp = []
    with open(filename, 'r') as infile:
        for line in infile:
            a,b,c,d,e,f,g,h = line.split()
            t.append(eval(a))
            e.append(eval(b))
            e_2.append(eval(c))
            mc.append(eval(d))
            cv.append(eval(e))
            m.append(eval(f))
            m_2.append(eval(g))
            acp.append(eval(h))
        infile.close()
    # 
    """t = np.asarray(t)
    e = np.asarray(e)
    e_2 = np.asarray(e_2)
    mc = np.asarray(mc)
    cv = np.asarray(cv)
    m = np.asarray(m)
    m_2 = np.asarray(m_2)
    acp = np.asarray(acp)"""
    return t,e,e_2,mc,cv,m,m_2,acp


def main():
    readfile()


if __name__=='__main__':
    main()
