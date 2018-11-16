#!/usr/bin/env python3
import matplotlib.pyplot as plt
import numpy as np


def plot_probability():
    """
    Reads binary files (with int32) from data folder
    plots four plots
    """
    mcfilepath = "data/equiltime_MC.bin"
    mc = np.fromfile(mcfilepath, dtype=np.int32)
    c = 221
    for T,t in zip([1.0, 2.4], ['_T1','_T2']):
        for title,o in zip(["Ordered","Random"],['_1','_0']): # 1: ordered init state, 0: random init state
            pfilepath = "data/Eprob" + o + t + ".bin"
            p = np.fromfile(pfilepath, dtype=np.int32)

            plt.subplot(c)
            if c < 223:
                plt.title("20x20 lattice " + title + " initial state")
            c += 1
            emin = p[0];emax = p[1];mean = p[2];std = p[3];energylist = p[4:]
            Normalization = 9700000.
            e = np.asarray(energylist)/Normalization
            top = np.max(e)
            E = np.linspace(emin, emax, len(energylist))
            plt.bar(E, e,label="T=%1.1f" %T,width=4, edgecolor="g")
            if T==2.4:
                plt.plot(E,top*np.exp(-(E-mean)**2/(2*std**2)),'y-',label='Gaussian fit')
            plt.plot([mean,mean],[0,top],'r-',label=r'$\mu = %1.1f, \sigma_E=%1.1f$' %(mean,std))
            plt.xlabel("Energy [J]")
            plt.ylabel("Probability P(E)")
            plt.grid()
            plt.legend(loc="best")
    plt.show()


def plot_E_M_vs_MC():
    """
    Reads binary files (with int32) from data folder
    plots four plots
    """
    mcfilepath = "data/equiltime_MC.bin"
    mc = np.fromfile(mcfilepath, dtype=np.int32)
    c = 221
    for var in ['E','M']:
        for title,o in zip(["Ordered","Random"],['_1','_0']):
            filepath1 = "data/equiltime" + o + "_T1_" + var +".bin"
            filepath2 = "data/equiltime" + o + "_T2_" + var +".bin"
            y1 = np.fromfile(filepath1, dtype=np.int32)
            y2 = np.fromfile(filepath2, dtype=np.int32)

            plt.subplot(c)
            if c < 223:
                plt.title("20x20 lattice " + title + " initial state")
                plt.ylabel("Energy [J] per spin")
            else:
                plt.xlabel("MC cycles")
                plt.ylabel("Magnetization per spin")
            c += 1
            plt.plot(mc,y1/400.,label='T=1.0')
            plt.plot(mc,y2/400.,label='T=2.4')
            plt.grid()
            plt.legend(loc="best")
    plt.show()


def plot_accepted():
    filepath0 = "data/acc_mc.bin"
    mc = np.fromfile(filepath0, dtype=np.int32)
    filepath1 = "data/acceptedconfigs_MC.bin"
    ac_mc = np.fromfile(filepath1, dtype=np.int32)
    plt.figure()
    plt.plot(mc, ac_mc,label="Temperature T = 1.0")
    plt.xlabel('Number of Monte Carlo cycles')
    plt.ylabel('Number of accepted configurations')
    plt.grid()
    plt.legend()
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
    cv_s = [];chi_s = [];temp_s = [];mag_s = [];ene_s = []
    for lattice_nr in lattices:
        spins = float(eval(lattice_nr))**2
        T = [];E = [];E2 = [];M = [];M2 = []
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

    plt.subplot(223)
    for t,chi,name in zip(temp_s,chi_s,lattices):
        plt.plot(t,chi/t,'k.')
        plt.plot(t,chi/t,'-',label="L = " + name)
    plt.xlabel(r"$k_B T$")
    plt.ylabel(r"$\chi$")
    plt.legend()
    plt.grid()

    plt.subplot(222)
    for t,m,name in zip(temp_s,mag_s,lattices):
        plt.plot(t,m,'k.')
        plt.plot(t,m,'-',label="L = " + name)
    plt.xlabel(r"$k_B T$")
    plt.ylabel(r"$\langle |M| \rangle$")
    plt.legend()
    plt.grid()

    plt.subplot(221)
    for t,e,name in zip(temp_s,ene_s,lattices):
        plt.plot(t,e,'k.')
        plt.plot(t,e,'-',label="L = " + name)
    plt.xlabel(r"$k_B T$")
    plt.ylabel(r"$E$ per spin $[J]$")
    plt.legend()
    plt.grid()

    plt.subplot(224)
    for t,cv,name in zip(temp_s,cv_s,lattices):
        plt.plot(t,cv/t**2,'k.')
        plt.plot(t,cv/t**2,'-',label="L = " + name)
    plt.xlabel(r"$k_B T$")
    plt.ylabel(r"$C_V$  $[J k_B]$")
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
    inf = np.append(t_inf_cv, t_inf_chi)
    print("%1.3f +/- %1.3f" % (np.mean(inf),np.std(inf)))

def main():
    plt.rcParams.update({'font.size': 14})
    # plot_probability()
    # plot_E_M_vs_MC()
    # plot_accepted()
    plot_lattice_L()


if __name__=='__main__':
    main()
