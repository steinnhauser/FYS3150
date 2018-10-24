# Earth-Sun System
Initial conditions are specified in the main.cpp file. Here it can also be decided to simulate system using Euler's method or the velocity Verlet method. The simulations can be run and visualized by running:
```
$ make -j
$ ./test.x
$ python3 plot.py eulerdata
$ python3 plot.py verletdata
```
In plot.py it can be specified to plot the positions, energy vs. time and angular momentum vs. time
