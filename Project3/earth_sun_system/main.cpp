#include <iostream>
#include <string>
#include <math.h>
#include "eulers_method.h"
#include "verlet_method.h"
#include "write_vectors_function.h"

using namespace arma;

int main(int argc, char* argv[])
{
  double T = 10;
  double dt = 0.0001;
  int N = T/dt + 1;
  // initial conditions
  double x0 = 1.0;
  double y0 = 0;
  double z0 = 0;
  double xv0 = 0;
  double yv0 = 0.99*2*M_PI; // One rotation per year + circular motion
  double zv0 = 0;

  vec x_pos1 = zeros<vec>(N);
  vec y_pos1 = zeros<vec>(N);
  vec z_pos1 = zeros<vec>(N);
  vec kin_energy1 = zeros<vec>(N);
  vec pot_energy1 = zeros<vec>(N);

  vec x_pos2 = zeros<vec>(N);
  vec y_pos2 = zeros<vec>(N);
  vec z_pos2 = zeros<vec>(N);
  vec kin_energy2 = zeros<vec>(N);
  vec pot_energy2 = zeros<vec>(N);

  vec t = linspace<vec>(0,(N-1)*dt,N);

  eulers_method_calculate(x0, y0, z0, xv0, yv0, zv0, N, dt, x_pos1, y_pos1, z_pos1, kin_energy1, pot_energy1);
  verlet_method_calculate(x0, y0, z0, xv0, yv0, zv0, N, dt, x_pos2, y_pos2, z_pos2, kin_energy2, pot_energy2);

  write_vectors(x_pos1, y_pos1, z_pos1, kin_energy1, pot_energy1, t, "eulerdata", "Euler's method");
  write_vectors(x_pos2, y_pos2, z_pos2, kin_energy2, pot_energy2, t, "verletdata", "velocity Verlet method");

  return 0;
}
