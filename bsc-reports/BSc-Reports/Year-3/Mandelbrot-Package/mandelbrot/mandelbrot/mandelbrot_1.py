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
    dx = (xmax-xmin)/Nx
    dy = (ymax-ymin)/Ny #Step lengths for values (resolution of grid)
    xl = np.linspace(xmin, xmax, Nx)
    yl = np.linspace(ymin, ymax, Ny)
    picture = np.zeros((Nx,Ny))
    for i in range(Nx):
        for j in range(Ny):
            c = (xmin + i*dx) + (ymin + j*dy)*1j #Initial value of the complex number z.
            z = 0
            counter = 0 #Counts how many iterations it takes before modulus exceeds 2.
            while abs(z)<2 and counter<escape_time: #Implemented a maximal value where the loop breaks.
                z = z**2 + c #Generating the mandelbrot set
                counter+=1 #Counting how many iterations it takes for the loop to exit.
            picture[j][i]=counter
    tm.test_init_rect_inside(xmin, xmax, ymin, ymax, escape_time, picture)
    return xl, yl, picture



if __name__=="__main__":
    if len(sys.argv)!=3:
        print("Input error. Input grid resolution and escape time as argument.")
        exit()

    N = int(sys.argv[1])
    escape_time = int(sys.argv[2])

    Nx=N #Number of points in the x-axis
    Ny=N #Number of points in the y-axis

    xmin, xmax = -1.7, 0.6 #Initial value to calculate, "bottom-left corner" of the rectangle.
    ymin, ymax = -1.5, 1.5 #"Top-right corner" of the rectangle.


    start_time = time.time() #Note time at beginning of calculations.
    xl, yl, picture = mandelbrot(xmin, xmax, ymin, ymax, Nx, Ny, escape_time)
    end_time = time.time() - start_time #Note time at the end of calculation.
    print("Took %.2f seconds to calculate for %i grid mesh points." %(end_time,N**2))
    plt.contourf(xl, yl, picture, cmap="inferno")
    plt.show()


"""
Program execution example:

steinn@steinn-VirtualBox:~/Desktop/INF3331-steinnhm/assignment4$ python3 mandelbrot_1.py 2000 100
Took 34.85 seconds to calculate for 4000000 grid mesh points.
"""
