#!/usr/bin/env python3
import matplotlib.pyplot as plt
import numpy as np


def readfile_mc(filename):
    """
    Read data from one data files, where #MC cycles (proportional to time)
    is varied, energies and magnetization as functions of time.
    And at last accepted configurations vs. #MC cycles.

    Returns lists of data
    """
    mc = []; e = []; m = []
    with open(filename, 'r') as infile:
        infile.readline()
        for line in infile:
            mcv,ev,mv = line.split()
            mc.append(eval(mcv))
            e.append(eval(ev))
            m.append(eval(mv))
        infile.close()
    return mc,e,m


def plot_equilibration_time():
    energies=[];magnet=[];mclist=[]
    # Obtain and save data from files
    for o in ['_1','_0']: # 1: ordered init state, 0: random init state
        for T,t in zip([1,2.4],['_T1','_T2']):
            filename = "equiltime" + o + t + ".txt"
            mc,e,m = readfile_mc(filename)
            energies.append(e)
            magnet.append(m)
            mclist.append(mc)
    # energy plot
    c = 0
    # c=0: ordered, T = 1.0
    # c=1: ordered, T = 2.4
    # c=2: random,  T = 1.0
    # c=3: random,  T = 2.4
    for o in ['Ordered','Random']:
        plt.figure()
        plt.title(o + ' initial state')
        for T in [1,2.4]:
            plt.plot(mclist[c],energies[c],label='T=%1.1f'%T)
            c += 1
        plt.xlabel('Number of Monte Carlo cycles')
        plt.ylabel(r'$\langle E \rangle$')
        plt.legend()
        plt.grid()
        plt.show()
    # Magnetization plot
    c = 0
    for o in ['Ordered','Random']:
        plt.figure()
        plt.title(o + ' initial state')
        for T in [1,2.4]:
            plt.plot(mclist[c],magnet[c],label='T=%1.1f'%T)
            c += 1
        plt.xlabel('Number of Monte Carlo cycles')
        plt.ylabel(r'$\langle |M| \rangle$')
        plt.legend()
        plt.grid()
        plt.show()


def plot_E_probability():
    for o in ['_1','_0']: # 1: ordered init state, 0: random init state
        for T,t in zip([1.0, 2.4],['_T1','_T2']):
            energylist=[]
            filename = "Eprob" + o + t + ".txt"
            infile = open(filename, "r")

            emin = eval(infile.readline())
            emax = eval(infile.readline())
            mean = eval(infile.readline())
            std = eval(infile.readline())

            for line in infile:
                energylist.append(int(line))

            print(energylist)
            E = np.linspace(emin, emax, len(energylist))
            plt.bar(E, energylist,\
            label="T=%1.1f, $\\mu = %1.1f$, $\\sigma_E=%1.1f$" %(T,mean,std), \
            width=4, edgecolor="g")
        if o=="_1":
            plt.title("20x20 lattice Ordered initial state.")
        else:
            plt.title("20x20 lattice with Disordered initial state.")
        plt.xlabel("Energy level [J]")
        plt.ylabel("Number counted []")
        plt.grid()
        plt.legend(loc="best")
        plt.show()


def readfile_acc(filename):
    temp = []; accpt = []
    with open(filename, 'r') as infile:
        infile.readline()
        for line in infile:
            tv,av = line.split()
            temp.append(eval(tv))
            accpt.append(eval(av))
        infile.close()
    return temp, accpt


def plot_accepted():
    temp,accpt = readfile_acc("acceptedconfigs.txt")
    plt.figure()
    plt.plot(temp,accpt)
    plt.xlabel('Temperature [kT/J]')
    plt.ylabel('avg. Accepted Configurations')
    plt.grid()
    plt.show()


def main():
    #plot_equilibration_time()
    #plot_accepted()
    plot_E_probability()



if __name__=='__main__':
    main()
