#!/usr/bin/python3
import matplotlib.pyplot as plt
import mpl_toolkits.mplot3d.axes3d as p3
import matplotlib.animation as ani
import numpy as np

number_of_planets = 2

def readfile(file_number):
    """read data from one data file,
    save, and return name of planet and
    arrays of x, y, z and t"""
    filename = "./data/planet" + str(file_number) + ".txt"
    xl = []; yl = []; zl = []; tl = []
    with open(filename, 'r') as infile:
        planet = infile.readline().split()[0]
        print(planet)
        infile.readline();
        for line in infile:
            xval, yval, zval, tval = line.split()
            xl.append(eval(xval))
            yl.append(eval(yval))
            zl.append(eval(zval))
            tl.append(eval(tval))
        infile.close()
    x = np.asarray(xl)
    y = np.asarray(yl)
    z = np.asarray(zl)
    t = np.asarray(tl)
    return planet, x, y, z, t


def planetdata(number_of_planets):
    """generate an array data, set up
    correctly for a 3d animation"""
    data = []
    for i in range(number_of_planets):
        planet, x, y, z, t = readfile(i)
        data_one_planet = [x, y, z]
        data.append(data_one_planet)
    return np.asarray(data)


def animate_3D(data):
    N = len(data[0][0])
    fig = plt.figure()
    ax = p3.Axes3D(fig)
    limit = [-0.5, 0.5]
    ax.set_xlim3d(limit)
    ax.set_ylim3d(limit)
    ax.set_zlim3d(limit)
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')

    def update_lines(num, dataLines, lines):
        for line, data in zip(lines, dataLines):
            line.set_data(data[0:2, :num])
            line.set_3d_properties(data[2, :num])
            #line.set_marker("o")
        return lines

    lines = [ax.plot(dat[0, 0:1], dat[1, 0:1], dat[2, 0:1])[0] for dat in data]
    line_ani = ani.FuncAnimation(fig, update_lines, N, fargs=(data, lines),
                                 interval=1, blit=False)
    plt.show()


def lin(x,y,deg=1):
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
    m1,dm1 = mercury('pure: ','./data/mercury.txt')
    m2,dm2 = mercury('GR:   ','./data/mercury_GR.txt')
    diff = float(m2-m1)
    u = diff*np.sqrt((dm1/m1)**2 + (dm2/m2)**2)
    plt.title(r"Difference in slopes: (%3.1f $\pm$ %1.1f) arc sec/century" % (diff,u))
    plt.savefig("./data/perihel.pdf")
    animate_3D(planetdata(number_of_planets))


if __name__=='__main__':
    main()
