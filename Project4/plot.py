#!/usr/bin/env python3
import matplotlib.pyplot as plt
import numpy as np


def plot_equilibration_time():
    """Reads binary files (with int32) from data folder
    plots four plots"""
    mcfilepath = "data/equiltime_MC.bin"
    mc = np.fromfile(mcfilepath, dtype=np.int32)
    for title,o in zip(["Ordered","Random"],['_1','_0']): # 1: ordered init state, 0: random init state
        energies=[];magnet=[];probabilities=[]
        for T,t in zip([1.0, 2.4], ['_T1','_T2']):
            efilepath = "data/equiltime" + o + t + "_E.bin"
            mfilepath = "data/equiltime" + o + t + "_M.bin"
            pfilepath = "data/Eprob" + o + t + ".bin"
            energies.append(np.fromfile(efilepath, dtype=np.int32))
            magnet.append(np.fromfile(mfilepath, dtype=np.int32))
            p = np.fromfile(pfilepath, dtype=np.int32)


            #total 1000000,
            Normalization = 9700000.

            plt.title("20x20 lattice " + title + " initial state,\nTotal of 9.7e6 MC cycles.")

            emin = p[0]
            emax = p[1]
            mean = p[2]
            std = p[3]
            energylist = p[4:]
            e = np.asarray(energylist)/Normalization
            top = np.max(e)
            E = np.linspace(emin, emax, len(energylist))
            plt.bar(E, e,\
            label="T=%1.1f" %T, \
            width=4, edgecolor="g")
            if T==2.4:
                plt.plot(E,top*np.exp(-(E-mean)**2/(2*std**2)),'y-',label='Gaussian fit')
            plt.plot([mean,mean],[0,top],'r-',label=r'$\mu = %1.1f, \sigma_E=%1.1f$' %(mean,std))
            plt.xlabel("Energy [J]")
            plt.ylabel("Probability P(E)")
            plt.grid()
            plt.legend(loc="best")
            plt.figure()

        """
        plt.title(title + ' initial state')
        plt.plot(mc,energies[0]/400.,label='T=1.0')
        plt.plot(mc,energies[1]/400.,label='T=2.4')
        plt.xlabel('Number of Monte Carlo cycles')
        plt.ylabel(r'E')
        plt.legend()
        plt.grid()
        plt.figure() # energy plot

        plt.title(title + ' initial state')
        plt.plot(mc,magnet[0]/400.,label='T=1.0')
        plt.plot(mc,magnet[1]/400.,label='T=2.4')
        plt.xlabel('Number of Monte Carlo cycles')
        plt.ylabel(r'M')
        plt.legend()
        plt.grid()
        """

    plt.show()


def plot_accepted():
    filepath0 = "data/acc_mc.bin"
    mc = np.fromfile(filepath0, dtype=np.int32)
    filepath1 = "data/acceptedconfigs_MC.bin"
    ac_mc = np.fromfile(filepath1, dtype=np.int32)
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
    plt.ylabel(r'Avg. acc. configs. per MC cycle per spin')
    plt.grid()
    plt.show()


def plot_lattice_L():
    lattices = ["40", "60", "80" , "100", "120"]
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

    L = np.array([40,60,80,100,120])
    Tcv = np.zeros(5)
    Tchi = np.zeros(5)
    for i,t,cv,chi in zip(range(5),temp_s,cv_s,chi_s):
        Tcv[i] = t[np.argmax(cv)]
        Tchi[i] = t[np.argmax(chi)]

    t_inf_cv = np.zeros(10)
    t_inf_chi = np.zeros(10)
    c = 0
    print("CV              Chi")
    for i in range(5):
        for j in range(5):
            if i < j:
                t_inf_cv[c] = (Tcv[j]*L[j] - Tcv[i]*L[i]) / (L[j] - L[i])
                t_inf_chi[c] = (Tchi[j]*L[j] - Tchi[i]*L[i]) / (L[j] - L[i])
                print("%1.4f" % t_inf_cv[c], "         %1.4f" % t_inf_chi[c],)
                c += 1
    print("%1.3f +/- %1.3f" % (np.mean(t_inf_cv),np.std(t_inf_cv)), \
          "%1.3f +/- %1.3f" % (np.mean(t_inf_chi),np.std(t_inf_chi)))


def main():
    plt.rcParams.update({'font.size': 14})
    # plot_equilibration_time()
    # plot_accepted()
    plot_lattice_L()


if __name__=='__main__':
    main()
