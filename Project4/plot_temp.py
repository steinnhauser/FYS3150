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
    print(4*np.cosh(a)+12)
    E = -32*J*np.sinh(a)/(4*np.cosh(a)+12)
    EE = 256*J*np.cosh(a)/(4*np.cosh(a)+12)
    CV = (EE - E*E)/(k*T*T)
    M = (8*np.exp(a)+4)/(4*np.cosh(a)+12)
    MM = (32*np.exp(a)+8)/(4*np.cosh(a)+12)
    CHI = (MM - M*M)/(k*T)
    return E, EE, M, MM, CV, CHI
