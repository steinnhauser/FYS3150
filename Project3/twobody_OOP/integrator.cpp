#include "integrator.h"

Integrator::Integrator(){}
Integrator::Integrator(Body P1, Body P2)
{
  Body p1 = P1;
  Body p2 = P2;
}

cube Integrator::solve_motion(double dt, double totaltime, void (*method)(double, Body, Body));
{
  int N = totaltime/dt + 1;
  cube positional_tensor;
  positional_tensor = zeros<cube>(3,N,2);
  for (int t=0; t<N; t++){
    (*method)(p1, p2, dt);
    positional_tensor[0,t,0] = p1.x;
    positional_tensor[1,t,0] = p1.y;
    positional_tensor[2,t,0] = p1.z;
    positional_tensor[0,t,1] = p2.x;
    positional_tensor[1,t,1] = p2.y;
    positional_tensor[2,t,1] = p2.z;
  }
  return positional_tensor;
}
