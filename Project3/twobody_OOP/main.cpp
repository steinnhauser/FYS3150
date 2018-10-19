#include <iostream>
#include <string>
#include <math.h>
#include "body.h"
#include "integrator.h"
#include "euler.h"
#include "verlet.h"
#include "writefiles.h"

using namespace arma;

int main(int argc, char* argv[])
{
  double T = 0.1; //no. of Julian years simulated
  double dt = 0.001;
  int N = T/dt + 1;
  vec time_vec = linspace<vec>(0,T,N);

  // initial conditions in AU and AU/yr
  Body earth; Body sun;
  sun = Body(1, -0.1, 0, 0, 0, 0, 0);
  earth = Body(3e-6, 10.0, 0, 0, 0, 2*M_PI, 0);

  Integrator integrator_instance;
  integrator_instance = Integrator(sun, earth);

  string method1 = "euler";
  cube euler_pos = integrator_instance.solve_motion(dt,T,&euler_step);
  write_files(euler_pos, time_vec, method1);
  /*
  string method2 = "verlet";
  cube verlet_pos = integrator_instance.solve_motion(dt,T,&verlet_step);
  write_files(verlet_pos, time_vec, method2);
  */
  return 0;
}
