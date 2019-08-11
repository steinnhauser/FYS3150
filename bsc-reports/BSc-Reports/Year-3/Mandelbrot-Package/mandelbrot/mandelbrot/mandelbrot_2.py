#!user/bin/python3

import numpy as np
import matplotlib.pyplot as plt
import sys
import time

if __name__ == '__main__':
    import test_mandelbrot as tm
else:
    import mandelbrot.test_mandelbrot as tm


def mandelbrot(xmin, xmax, ymin, ymax, Nx, Ny, escape_time):
    tm.test_init_rect_outside(xmin, xmax, ymin, ymax)
    dx = (xmax-xmin)/float(Nx)
    dy = (ymax-ymin)/float(Ny) #Step lengths for values (resolution of grid)
    xl = np.linspace(xmin, xmax, Nx)
    yl = np.linspace(ymin, ymax, Ny)

    ypicture, xpicture = np.mgrid[ymin:ymax:dy, xmin:xmax:dx]

    contourvalues, z = np.zeros((Nx, Ny)), np.zeros((Nx, Ny),dtype=np.complex64)
    #initial_picture = np.zeros(z.shape)
    initial_picture = xpicture + ypicture*1j
    for i in range(escape_time-1):
        ind = abs(z)<2
        z[ind] = np.square(z[ind]) + initial_picture[ind]
        contourvalues[:][:]+=abs(z)<2

    tm.test_init_rect_inside(xmin, xmax, ymin, ymax, escape_time, contourvalues)
    return xl, yl, contourvalues




if __name__=="__main__":
    if len(sys.argv)!=3:
        print("Input error. Input grid resolution and escape time as argument.")
        exit()

    N = int(sys.argv[1])
    escape_time = int(sys.argv[2])

    Nx = N #Number of points in the x-axis
    Ny = N #Number of points in the y-axis

    xmin, xmax = -1.7, 0.6 #Initial value to calculate, "bottom-left corner" of the rectangle.
    ymin, ymax = -1.5, 1.5 #"Top-right corner" of the rectangle.

    start_time = time.time() #Note time at beginning of calculations.
    xl, yl, picture = mandelbrot(xmin, xmax, ymin, ymax, Nx, Ny, escape_time)
    end_time = time.time() - start_time #Note time at the end of calculation.
    print("Took %.2f seconds to calculate for %i grid mesh points." %(end_time,N**2))

    plt.contourf(xl, yl, picture, cmap="inferno")
    plt.title("Mandelbrot set with %i^2 mesh points and escape time %i" %(N, escape_time))
    plt.ylabel("Imaginary numbers")
    plt.xlabel("Real numbers")
    plt.show()


"""
Execution example:

steinn@steinn-VirtualBox:~/Desktop/INF3331-steinnhm/assignment4$ python3 mandelbrot_2.py 2000 100
Took 9.97 seconds to calculate for 4000000 grid mesh points.
"""
