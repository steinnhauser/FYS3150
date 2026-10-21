#!/usr/bin/python3
from .mandelbrot_3 import mandelbrot #Arbitrarily chose method two. The other two can also be chosen.
import matplotlib.pyplot as plt

def compute_mandelbrot(xmin, xmax, ymin, ymax, Nx, Ny, max_escape_time, plot_filename=None):
	xl, yl, image = mandelbrot(xmin, xmax, ymin, ymax, Nx, Ny, max_escape_time) #Compute mandelbrot
	plt.contourf(xl, yl, image, cmap="bone_r") #Plot it
	plt.colorbar()
	plt.title("Mandelbrot set with %ix%i mesh points and escape time %i" %(Nx, Ny, max_escape_time))
	plt.ylabel("Imaginary numbers")
	plt.xlabel("Real numbers")
	plt.show()
	if plot_filename != None: #If a filename is specified, save the figure.
		plt.contourf(xl, yl, image, cmap="bone_r")
		plt.colorbar()
		plt.title("Mandelbrot set with %ix%i mesh points and escape time %i" %(Nx, Ny, max_escape_time))
		plt.ylabel("Imaginary numbers")
		plt.xlabel("Real numbers")
		plt.savefig(plot_filename)
		print("Figure saved as %s.png" %plot_filename)
