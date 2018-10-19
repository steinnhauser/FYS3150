#include "integrator.h"

Integrator::Integrator(){}
Integrator::Integrator(Body P1, Body P2)
{
  Body p1 = P1;
  Body p2 = P2;
}

cube Integrator::solve_motion_euler(double dt, double totaltime)
{
  int N = totaltime/dt + 1;
  cube positional_tensor;
  positional_tensor = zeros<cube>(3,N,2);
  for (int timestep=0; timestep<N; timestep++) {
    for (int body=0; body<2; body++) {
      positional_tensor(0,timestep,body) = p1.x;
      positional_tensor(1,timestep,body) = p1.y;
      positional_tensor(2,timestep,body) = p1.z;
    }
    method(p1, p2, dt);
  }
  return positional_tensor;
}

cube Integrator::solve_motion_verlet(double dt, double totaltime)
{
  int N = totaltime/dt + 1;
  cube positional_tensor;
  positional_tensor = zeros<cube>(3,N,2);
  for (int timestep=0; timestep<N; timestep++) {
    for (int body=0; body<2; body++) {
      positional_tensor(0,timestep,body) = p1.x;
      positional_tensor(1,timestep,body) = p1.y;
      positional_tensor(2,timestep,body) = p1.z;
    }
    method(p1, p2, dt);
  }
  return positional_tensor;
}
