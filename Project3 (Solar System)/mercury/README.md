# Mercury's Perihelion Precession
The entire simulation of Mercury's perihelion precession is done in main.cpp, which is specified for the only purpose of recording perihelion events (with correct angle and time) for the desired time duration and time step. The program is used to construct files 'mercury_pure.txt' (classical physics) and 'mercury.txt' (general relativity). Run:
```
$ make
$ ./test.x
```
The plot.py is set up to find the slope of angle/time for both files, but can easily be modified to look at only one of the files. Run:
```
$ python3 plot.py
```
