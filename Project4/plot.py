#!/usr/bin/env python3
import matplotlib.pyplot as plt
import numpy as np


def plot_equilibration_time():
    """Reads binary files (with int32) from data folder
    plots four plots"""
    mcfilepath = "data/equiltime_MC.bin"
    variance=[]
    mc = np.fromfile(mcfilepath, dtype=np.int32)
    for title,o in zip(["Ordered","Random"],['_1','_0']): # 1: ordered init state, 0: random init state
        energies=[];magnet=[];probabilities=[]
        for T,t in zip([1.0, 2.4], ['_T1','_T2']):
            efilepath = "data/equiltime" + o + t + "_E.bin"
            mfilepath = "data/equiltime" + o + t + "_M.bin"
            vfilepath = "data/equiltime" + o + t + "_V.bin"
            pfilepath = "data/Eprob" + o + t + ".bin"
            energies.append(np.fromfile(efilepath, dtype=np.int32))
            magnet.append(np.fromfile(mfilepath, dtype=np.int32))
            variance.append(np.fromfile(vfilepath, dtype=np.int32))
            p = np.fromfile(pfilepath, dtype=np.int32)

            plt.figure() # probability plot
            plt.title("20x20 lattice " + title + " initial state")
            emin = p[0]
            emax = p[1]
            mean = p[2]
            std = p[3]
            energylist = p[4:]
            e = np.asarray(energylist)
            top = np.max(e)
            E = np.linspace(emin, emax, len(energylist))
            plt.bar(E, energylist,\
            label="T=%1.1f, $\\mu = %1.1f$, $\\sigma_E=%1.1f$" %(T,mean,std), \
            width=4, edgecolor="g")
            plt.plot(E,top*np.exp(-(E-mean)**2/(2*std**2)))
            plt.xlabel("Energy level [J]")
            plt.ylabel("Number counted []")
            plt.grid()
            plt.legend(loc="best")
            plt.show()

        plt.figure() # energy plot
        plt.title(title + ' initial state')
        plt.plot(mc,energies[0]/400,label='T=1.0')
        plt.plot(mc,energies[1]/400,label='T=2.4')
        plt.xlabel('Number of Monte Carlo cycles')
        plt.ylabel(r'E')
        plt.legend()
        plt.grid()
        plt.show()

        plt.figure() # Magnetization plot
        plt.title(title + ' initial state')
        plt.plot(mc,magnet[0]/400,label='T=1.0')
        plt.plot(mc,magnet[1]/400,label='T=2.4')
        plt.xlabel('Number of Monte Carlo cycles')
        plt.ylabel(r'M')
        plt.legend()
        plt.grid()
        plt.show()

    plt.figure() # Magnetization plot
    plt.title('Random initial state, T=1.0')
    plt.plot(mc[4:],variance[2])
    plt.xlabel('Number of Monte Carlo cycles')
    plt.ylabel(r'$Variance, \sigma_E^2, [J^2]$')
    # plt.legend()
    plt.grid()
    plt.show()


def plot_accepted():
    filepath0 = "data/acc_mc.bin"
    mc = np.fromfile(filepath0, dtype=np.int32)
    filepath1 = "data/acceptedconfigs_MC.bin"
    ac_mc = np.fromfile(filepath1, dtype=np.float64)
    plt.figure()
    plt.title("Temperature T = 1.0")
    plt.plot(mc, ac_mc)
    plt.xlabel('Number of Monte Carlo cycles')
    plt.ylabel('Number of accepted configurations')
    plt.grid()
    plt.show()

    filepath2 = "data/acceptedconfigs_T.bin"
    ac_T = np.fromfile(filepath2, dtype=np.float64)
    filepath3 = "data/acc_temps.bin"
    temps = np.fromfile(filepath3, dtype=np.float64)
    plt.figure()
    plt.plot(temps,ac_T)
    plt.xlabel('Temperature [kT/J]')
    plt.ylabel(r'Avg. acc. configs. per MC cycle')
    plt.grid()
    plt.show()


def plot_lattice_L():
    lattices = ["40", "60", "80", "100"]
    cv_s = []
    chi_s = []
    temp_s = []
    mag_s = []
    ene_s = []
    for lattice_nr in lattices:
        spins = float(eval(lattice_nr))**2
        T = []
        E = []
        E2 = []
        M = []
        M2 = []
        filename = "data/lattice_" + lattice_nr + ".txt"
        infile=open(filename, "r")
        infile.readline() #first line is indexing
        for line in infile:
            a = line.split()
            T.append(eval(a[0]))
            E.append(eval(a[1]))
            E2.append(eval(a[2]))
            M.append(eval(a[3]))
            M2.append(eval(a[4]))
        M = np.asarray(M)
        M2 = np.asarray(M2)
        E = np.asarray(E)
        E2 = np.asarray(E2)
        T = np.asarray(T)
        temp_s.append(T)
        chi_s.append(M2 - (M*M*spins))
        cv_s.append(E2 - (E*E*spins))
        mag_s.append(np.abs(M))
        ene_s.append(E)

    for t,chi,name in zip(temp_s,chi_s,lattices):
        plt.plot(t,chi,'k.')
        plt.plot(t,chi,'-',label="L = " + name)
    plt.xlabel(r"$T$")
    plt.ylabel(r"$\chi$")
    plt.legend()
    plt.grid()
    plt.figure()

    for t,m,name in zip(temp_s,mag_s,lattices):
        plt.plot(t,m,'k.')
        plt.plot(t,m,'-',label="L = " + name)
    plt.xlabel(r"$T$")
    plt.ylabel(r"$\langle |M| \rangle$")
    plt.legend()
    plt.grid()
    plt.figure()

    for t,e,name in zip(temp_s,ene_s,lattices):
        plt.plot(t,e,'k.')
        plt.plot(t,e,'-',label="L = " + name)
    plt.xlabel(r"$T$")
    plt.ylabel(r"$\langle E \rangle$")
    plt.legend()
    plt.grid()
    plt.figure()

    for t,cv,name in zip(temp_s,cv_s,lattices):
        plt.plot(t,cv,'k.')
        plt.plot(t,cv,'-',label="L = " + name)
    plt.xlabel(r"$T$")
    plt.ylabel(r"$C_V$")
    plt.legend()
    plt.grid()
    plt.show()



def main():
    # plot_equilibration_time()
    # plot_accepted()
    plot_lattice_L()


if __name__=='__main__':
    main()
