#include <iostream>
#include <string>
#include <math.h>
#include "planet.h"
#include "solver.h"
#include "eulers_method.h"
#include "verlet_method.h"
#include "write_vectors_function.h"

using namespace arma;

int main(int argc, char* argv[])
{
  double T = 5; //no. of Julian years simulated
  double dt = 0.001;
  int N = T/dt + 1;
  // initial conditions in AU and AU/yr
  planet earth; planet sun;
  earth = planet(1, 0, 0, 0, 0, 0, 0);
  sun = planet(3e-6, 1, 0, 0, 0, 2*M_PI, 0);

  solver solver_instance;
  solver_instance = solver(dt,T,earth,sun);
  cube euler_pos = solver_instance.solve_motion();
  cube verlet_pos = solver_instance.solve_motion();

  return 0;
}
