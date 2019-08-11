#!usr/bin/python3

import numpy as np
import matplotlib.pyplot as plt
import time
from numba import jit
import sys

if __name__ == '__main__':
    import test_mandelbrot as tm
else:
    import mandelbrot.test_mandelbrot as tm

if len(sys.argv)==1:
    print("Input error. Input calculation command (1, 2 or 3), grid resolution and escape time as argument.")
    print("To see the user manual, input >python3 mandelbrot.py --help")
    exit()

if len(sys.argv)!=4:
    if str(sys.argv[1])=="--help":
        print(" ")
        print("----------------------------------------USER MANUAL-----------------------------------------------")
        print("Input syntax is designed such that the first input declares which type of calculation is requested.")
        print("Input 1 for a normal python calculation, 2 for a numpy calculation, and 3 for a numba calculation (jit)")
        print("The second input declares the number of grid mesh points is requested for the calculation.")
        print("If input equals 1000, then the mesh grid will consist of 1000^2, or a million mesh points.")
        print("The third input declares the escape time of the calculation.")
        print("Typically this value is in the range from 30 to 100.")
        print("A larger value escape time produces a more accurate result, but takes considerably longer.")
        print("An example of how to produce an effective result is: >python3 mandelbrot.py 3 4000 60")
        print("-------------------------------------------------------------------------------------")
        exit()
    print("Input error. Input calculation command (1, 2 or 3), grid resolution and escape time as argument.")
    print("To see the user manual, input >python3 mandelbrot.py --help")
    exit()

type = int(sys.argv[1])
N = int(sys.argv[2])
max_escape_time = int(sys.argv[3])

#Collect boarder values from the user.
print("Would you like to customize the calculation yourself?")
print("If not, the mesh grid will be square, %i x %i." %(N,N))
ans1 = str(input("Choosing Y will overwrite N and escape time values specified. (Y/N): "))
if(ans1=="Y"):
    xmin = float(input("Input bottom left corner x-value: "))
    ymin = float(input("Input bottom left corner y-value: "))
    xmax = float(input("Input top right corner x-value: "))
    ymax = float(input("Input top right corner y-value: "))
    tm.test_init_rect_outside(xmin, xmax, ymin, ymax) #Checking if the points are inside the set.
    Nx = int(input("Input number of mesh grid points in the x-direction: "))
    Ny = int(input("Input number of mesh grid points in the y-direction: "))
    max_escape_time = float(input("Input escape time: "))
elif(ans1=="N"):
    xmin, xmax = -1.6, 0.7 #Initial value to calculate, "bottom-left corner" of the rectangle.
    ymin, ymax = -1.5, 1.5 #"Top-right corner" of the rectangle. These values are a nice default.
    Nx=N
    Ny=N
else:
    print("Input error. Choose either Y or N")
    exit()

file_name = "from mandelbrot_%d import mandelbrot" %type
exec(file_name)

start_time = time.time() #Note time at beginning of calculations.
xl, yl, picture = mandelbrot(xmin, xmax, ymin, ymax, Nx, Ny, max_escape_time)
end_time = time.time() - start_time #Note time at the end of calculation.
print("Took %i seconds to calculate for %i grid mesh points.\n" %(end_time,N**2))

#Test if all elements are inside or outside the mandelbrot set:


tm.test_init_rect_inside(xmin, xmax, ymin, ymax, max_escape_time, picture)



plt.contourf(xl, yl, picture, cmap="bone_r")
plt.colorbar()
plt.title("Mandelbrot set with %i^2 mesh points and escape time %i" %(N, max_escape_time))
plt.ylabel("Imaginary numbers")
plt.xlabel("Real numbers")
plt.show() #Shows figure so that the user can decide whether it is worth a save.


plt.contourf(xl, yl, picture, cmap="bone_r")
plt.colorbar()
plt.title("Mandelbrot set with %i^2 mesh points and escape time %i" %(N, max_escape_time))
plt.ylabel("Imaginary numbers")
plt.xlabel("Real numbers")
#Collect the file name if the user wants to save the figure.
print("Would you like to save the results as a .png file? (Y/N)")
print("Choosing Y will save the figure in the folder of the python file.")
ans2 = str(input("Choosing N will not save the file: "))
if(ans2=="Y"):
    figure_name = str(input("Input file name: "))
    plt.savefig(figure_name)
    print("Figure saved.")
elif(ans2=="N"):
    print("Figure not saved.")
    exit()
else:
    print("Input error. Choose either Y or N")
    exit()
