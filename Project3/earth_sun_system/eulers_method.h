#ifndef Eulers_method_H
#define Eulers_method_H
#include <iostream>
#include <armadillo>
#include <math.h>

using namespace arma;

void eulers_method_calculate(double x0, double y0, double z0, double xv0, double yv0, double zv0, int N, double dt,
  vec &xpos, vec &ypos, vec &zpos, vec& kin_energy, vec & pot_energy, vec& ang_mom);

#endif
