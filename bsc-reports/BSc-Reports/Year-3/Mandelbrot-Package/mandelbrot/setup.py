#!usr/bin/python3

import matplotlib.pyplot as plt
import numpy as np
from distutils.core import setup
from mandelbrot import mandelbrot
from mandelbrot.test_mandelbrot import test_mandelbrot
#export PYTHONPATH=/home/Desktop/INF3331-steinnhm/assignment4:$PYTHONPATH
#pip install --upgrade setuptools.


setup(
    name = "Mandelbrot",
    version = "0.1.0",
    license = "LICENSE",
    packages = ['mandelbrot_1', 'mandelbrot_2', 'mandelbrot_3', 'mandelbrot', 'test_mandelbrot'],
    author = "Steinn Hauser",
    description = "A package to calculate various areas of the Mandelbrot set.",
    long_description = open("README.md").read(),
)
