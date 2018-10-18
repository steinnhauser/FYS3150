#include <iostream>
#include <string>
#include <math.h>
#include "body.h"
#include "integrator.h"
#include "euler.h"
#include "verlet.h"

using namespace arma;

int main(int argc, char* argv[])
{
  double T = 5; //no. of Julian years simulated
  double dt = 0.001;
  int N = T/dt + 1;
  // initial conditions in AU and AU/yr
  Body earth; Body sun;
  earth = Body(1, 0, 0, 0, 0, 0, 0);
  sun = Body(3e-6, 1, 0, 0, 0, 2*M_PI, 0);

  Integrator integrator_instance;
  integrator_instance = Integrator(dt,T,earth,sun);
  cube euler_pos = integrator_instance.solve_motion(euler_step);
  cube verlet_pos = integrator_instance.solve_motion(verlet_step);

  return 0;
}
