#include <iostream>
#include <string>
#include <math.h>
#include "eulers_method.h"
#include "verlet_method.h"
#include "write_vectors_function.h"
#include "test_functions.h"

using namespace arma;
using namespace std;

int main(int argc, char* argv[])
{
  /*
  Units used:
  1 unit of time = 1 yr
  1 unit of length = 1 AU
  1 unit of velocity = 1 AU/yr
  1 unit of mass = 1.99*10^30 kg = 1 mass_sun
  */
  double T = 10;
  double dt = 0.001;
  int N = T/dt + 1;
  vec t = linspace<vec>(0,(N-1)*dt,N);
  // initial conditions in AU and AU/yr
  double x0 = 1.;
  double y0 = 0;
  double z0 = 0;
  double xv0 = 0;
  double yv0 = 1.9*M_PI;//M_PI; // One rotation per year + circular motion, escape velocity = 8.89
  double zv0 = 0;

  // Eulers method
  string method1 = "Euler's method";
  vec x_pos1 = zeros<vec>(N);
  vec y_pos1 = zeros<vec>(N);
  vec z_pos1 = zeros<vec>(N);
  vec kin_energy1 = zeros<vec>(N);
  vec pot_energy1 = zeros<vec>(N);
  vec ang_mom1 = zeros<vec>(N);
  eulers_method_calculate(x0, y0, z0, xv0, yv0, zv0, N, dt, x_pos1, y_pos1, z_pos1, kin_energy1, pot_energy1, ang_mom1);
  test_energy_conservation(kin_energy1, pot_energy1, method1);
  test_angular_momentum_conservation(ang_mom1, method1);
  write_vectors(x_pos1, y_pos1, z_pos1, kin_energy1, pot_energy1, ang_mom1, t, "eulerdata", "Euler's method");

  // Velocity Verlet method
  string method2 = "Velocity Verlet method";
  vec x_pos2 = zeros<vec>(N);
  vec y_pos2 = zeros<vec>(N);
  vec z_pos2 = zeros<vec>(N);
  vec kin_energy2 = zeros<vec>(N);
  vec pot_energy2 = zeros<vec>(N);
  vec ang_mom2 = zeros<vec>(N);
  double beta = 2.0;
  verlet_method_calculate(x0, y0, z0, xv0, yv0, zv0, N, dt, x_pos2, y_pos2, z_pos2, kin_energy2, pot_energy2, ang_mom2, beta);
  test_energy_conservation(kin_energy2, pot_energy2, method2);
  test_angular_momentum_conservation(ang_mom2, method2);
  write_vectors(x_pos2, y_pos2, z_pos2, kin_energy2, pot_energy2, ang_mom2, t, "verletdata", "velocity Verlet method");

  return 0;
}
