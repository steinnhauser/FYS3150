#!/usr/bin/python3
import matplotlib.pyplot as plt
import numpy as np


def readfile():
    filename = "./data/positions.txt"
    xl = []; yl = [];
    with open(filename, 'r') as infile:
        for line in infile:
            xval, yval = line.split()
            xl.append(eval(xval))
            yl.append(eval(yval))
        infile.close()
    x = np.asarray(xl)
    y = np.asarray(yl)
    plt.plot(x,y)


def lin(x,y,deg=1):
    """Linear fit to data points with uncertainty"""
    p = np.polyfit(x,y,deg)
    yline = np.polyval(p,x)
    n = len(x)
    m = p[0]
    c = p[1]
    D = np.sum(x*x) - (np.sum(x))**2/n
    E = np.sum(x*y) - np.sum(x)*np.sum(y)/n
    F = np.sum(y*y) - (np.sum(y))**2/n
    dm = np.sqrt((1/(n - 2))*(D*F - E**2)/D**2)
    dc = np.sqrt((1/(n - 2))*(D/n + (np.mean(x))**2)*((D*F - E**2)/D**2))
    return m,dm,c,dc,yline


def mercury(gr,filename):
    """Study of Mercury's perihelion precession.
    Read's data of perihelion events with corresponding
    time and angle. Returns angular velocity and
    uncertainty obtained from lin()"""
    times = []; angles = []
    with open(filename, 'r') as infile:
        for line in infile:
            t,a = line.split()
            times.append(eval(t))
            angles.append(eval(a))
        infile.close()
    times = np.asarray(times)/100
    angles = np.asarray(angles)
    m,dm,c,dc,yline = lin(times,angles)
    plt.plot(times,angles,label=gr + 'recorded perihelion events')
    plt.plot(times,yline,label=gr + r'slope = %3.1f $\pm$ %1.1f' % (m,dm))
    plt.ylabel("arc sec")
    plt.xlabel("100 yr")
    plt.grid(True)
    plt.legend()
    return m,dm


def main():
    readfile()
    m1,dm1 = mercury('pure: ','./data/mercury.txt')
    m2,dm2 = mercury('GR:   ','./data/mercury_GR.txt')
    diff = float(m2-m1)
    u = np.sqrt(dm1**2 + dm2**2)
    plt.title(r"Difference in slopes: (%3.1f $\pm$ %1.1f) arc sec/century" % (diff,u))
    plt.show()

if __name__=='__main__':
    main()
