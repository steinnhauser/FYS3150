#!/usr/bin/python3
import matplotlib.pyplot as plt
import mpl_toolkits.mplot3d.axes3d as p3
import matplotlib.animation as ani
import numpy as np

number_of_planets = 4

def readfile(file_number):
    """read data from one data file,
    save, and return name of planet and
    arrays of x, y, z and t"""
    filename = "./data/planet" + str(file_number) + ".txt"
    xl = []; yl = []; zl = []; tl = []
    with open(filename, 'r') as infile:
        planet = infile.readline().split()[0]
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
    return planet, x[0:-1:30], y[0:-1:30], z[0:-1:30], t[0:-1:30]


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
    limit = [-2, 2]
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
                                 interval=150, blit=False)
    plt.show()


animate_3D(planetdata(number_of_planets))
