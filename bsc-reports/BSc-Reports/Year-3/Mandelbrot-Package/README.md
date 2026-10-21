# Mandelbrot package

The following package is designed to allow the user to choose
a rectangle of the complex plane and calculate the Mandelbrot
set for the specified region. The program has a Default setting
which illustrates what the total setting looks like (the region
covers the entire set, this is what I recommend running before
customizing).

## Various different methods include:
* Python only calculation of the Mandelbrot set
* Numpy only implementation
* Numba only implementation

The three variations of the method can be called from the command
line of the terminal window. This is further explained in the user
manual for the main program <mandelbrot.py>.
To bring up the user manual, write the following command:
python3 mandelbrot.py --help

## Prerequisites
There are several packages used in the program which need to be
installed for proper execution; matplotlib's pyplot package,
numpy's functions and numba's Git are the most central.

## Program execution
To execute the main program, the full Mandelbrot package must be
installed and saved in an appropriate manner (files which cooperate
are required to be in the same directory). Once this is properly
done, the program can be run in the following manner:
```
>python3 mandelbrot.py a b c
```
The variables a, b and c are command line arguments which dictate
the behavior of the code if it is not customized. The variable a
represents the method chosen (1, 2, 3), b represents the number of
mesh grid points, and c represents the escape time of the program.
A recommendation on how to run the program the first time is:
```
>python3 mandelbrot.py 3 3000 400
```

## Authors
Steinn Hauser Magnusson,
steinnhauser@mac.com

## License
Copyright (c) 2018 Steinn Hauser

Permission is hereby granted for use by anyone who has obtained this code.
Usage is free of charge unless otherwise is requested by the user.
No warranty of any kind.
