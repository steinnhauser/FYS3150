#!/usr/bin/env python3
import matplotlib.pyplot as plt
import numpy as np

"Plots for exercise 4c) study of equilibration time"

def readfile(filename):
    """
    Read data from one data files, where #MC cycles (proportional to time)
    is varied, energies and magnetization as functions of time.
    And at last accepted configurations vs. #MC cycles.

    Returns lists of data
    """
    mc = []; e = []; m = []; acp = []
    with open(filename, 'r') as infile:
        infile.readline()
        for line in infile:
            mcv,ev,mv,acpv = line.split()
            mc.append(eval(mcv))
            e.append(eval(ev))
            m.append(eval(mv))
            acp.append(eval(acpv))
        infile.close()
    return mc,e,m,acp


def plot_equilibration_time():
    energies=[];magnet=[]
    mclist=[];acplist=[]
    # Obtain and save data from files
    for o in [1,0]: # 1: ordered init state, 0: random init state
        for T,t in zip([1,2.4],['_T1','_T2']):
            filename = "datafile_" + str(o) + t + ".txt"
            mc,e,m,acp = readfile(filename)
            energies.append(e)
            magnet.append(m)
            mclist.append(mc)
            acplist.append(acp)

    # energy plot
    c = 0
    # c=0: ordered, T = 1.0
    # c=1: ordered, T = 2.4
    # c=2: random,  T = 1.0
    # c=3: random,  T = 2.4
    for o in ['Ordered','Random']:
        plt.figure()
        plt.title(o + 'initial state')
        for T in [1,2.4]:
            plt.plot(mclist[c],energies[c],label='T=%1.1f'%T)
            c += 1
        plt.xlabel('Number of Monte Carlo cycles')
        plt.ylabel(r'$\langle E \rangle$')
        plt.legend()
        plt.grid()
        plt.show()
        c += 1
    # Magnetization plot
    c = 0
    for o in ['ordered','random']:
        plt.figure()
        plt.title(o + 'initial state')
        for T in [1,2.4]:
            plt.plot(mclist[c],magnet[c],label='T=%1.1f'%T)
            c += 1
        plt.xlabel('Number of Monte Carlo cycles')
        plt.ylabel(r'$\langle |M| \rangle$')
        plt.legend()
        plt.grid()
        plt.show()
        c += 1
    # accepted configs vs. MC cycles
    plt.figure()
    for i,s in enumerate(["order T=1.0","order T=2.4","random T=1.0","random T=2.4"]):
        plt.plot(mclist[i],acplist[i],label=s)
    plt.xlabel('Number of Monte Carlo cycles')
    plt.ylabel('Accepted Configurations')
    plt.legend()
    plt.grid()
    plt.show()


def main():
    plot_equilibration_time()

if __name__=='__main__':
    main()
