#ifndef Verlet_method_H
#define Verlet_method_H
#include <iostream>
#include <armadillo>
#include <math.h>
using namespace arma;

vec verlet_method_calculate(double x0, double y0, double z0, double xv0, double yv0, double zv0, int N, double dt,
  vec& x_pos, vec& y_pos, vec& z_pos, vec& kin_energy, vec & pot_energy);

#endif
