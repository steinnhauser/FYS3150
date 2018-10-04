#ifndef Verlet_method_H
#define Verlet_method_H
#include<iostream>
#include<armadillo>
#include<math.h>
using namespace arma;

vec Verlet_method_calculate(double x0, double y0, double z0, double xv0, double yv0, double zv0, int N, double dt);

#endif
