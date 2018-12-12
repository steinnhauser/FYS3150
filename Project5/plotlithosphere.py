#!/usr/bin/env python3
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from mpl_toolkits.mplot3d import Axes3D
plt.rcParams.update({'font.size':12})
import numpy as np
import sys


def plot():
    files = [
        "data/lithosphere_Q.bin",
        "data/lithosphere.bin",
        "data/lithosphere_QR.bin"
    ]
    labels = ["Q = 0", "Natural Q", "Radioactive\nenrichment"]
    nx = 126
    ny = 101
    nt = 100
    for file,label in zip(files,labels):
        image = np.fromfile(file, dtype=float).reshape((ny,nx))
        temp = image[:,int(nx/2)]*1292 + 8
        depth = np.linspace(0,120,ny)
        plt.plot(depth,temp,label=label)
    plt.show()


if __name__=='__main__':
    plot()
    # animate2d()
