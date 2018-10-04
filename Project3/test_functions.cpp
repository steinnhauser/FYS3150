#include <armadillo>
#include <iostream>
#include <math.h>
#include "test_functions.h"

using namespace arma;

void test_energy_conservation(vec x_pos, vec y_pos, vec z_pos, vec x_vel, vec y_vel, vec z_vel, int N, double tolerance){
  vec kin_energy = zeros<vec>(N);
  vec pot_energy = zeros<vec>(N);
  double factor = 4*M_PI*M_PI;
  for (int i=0; i<N; i++) {
    kin_energy = 0.5*(x_vel(i)*x_vel(i) + y_vel(i)*y_vel(i) + z_vel(i)*z_vel(i));
    pot_energy = factor/(sqrt(x_pos(i)*x_pos(i) + y_pos(i)*y_pos(i) + z_pos(i)*z_pos(i)));
  }
}

void test_angular_momentum_conservation();
