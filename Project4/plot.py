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
    energies=[];magnet=[]
    # Obtain and save data from files
    mc = np.fromfile(mcfilepath, dtype=np.int32)
    for title,o in zip(["Ordered","Random"],['_1','_0']): # 1: ordered init state, 0: random init state
        for T,t in zip([1,2.4],['_T1','_T2']):
            efilepath = "data/equiltime" + o + t + "_E.bin"
            mfilepath = "data/equiltime" + o + t + "_M.bin"
            mcfilepath = "data/equiltime" + o + t + "_MC.bin"
            energies.append(np.fromfile(efilepath, dtype=np.int32))
            magnet.append(np.fromfile(mfilepath, dtype=np.int32))

        plt.figure() # energy plot
        plt.title(title + ' initial state')
        plt.plot(mc,energies,label='T=%1.1f'%T)
        plt.xlabel('Number of Monte Carlo cycles')
        plt.ylabel(r'$\langle E \rangle$')
        plt.legend()
        plt.grid()
        plt.show()

        plt.figure() # Magnetization plot
        plt.title(title + ' initial state')
        plt.plot(mc,m,label='T=%1.1f'%T)
        plt.xlabel('Number of Monte Carlo cycles')
        plt.ylabel(r'$\langle |M| \rangle$')
        plt.legend()
        plt.grid()
        plt.show()




def plot_E_probability():
    for o in ['_1','_0']: # 1: ordered init state, 0: random init state
        for T,t in zip([1.0, 2.4],['_T1','_T2']):
            energylist=[]
            """filename = "Eprob" + o + t + ".txt"
            infile = open(filename, "r")

            emin = eval(infile.readline())
            emax = eval(infile.readline())
            mean = eval(infile.readline())
            std = eval(infile.readline())"""

            filepath = "data/Eprob" + o + t + ".bin"

            bin_data = np.fromfile(filepath, dtype=np.int32)

            emin = bin_data[0]
            emax = bin_data[1]
            mean = bin_data[2]
            std = bin_data[3]

            for en in range(4, len(bin_data)):
                energylist.append(int(bin_data[en]))

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
    filepath = "Eprob_0_T1.txt"
    bin_data = np.fromfile(filepath, dtype=np.int32)
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
    plot_equilibration_time()
    plot_accepted()
    #plot_E_probability()



if __name__=='__main__':
    main()
