#include "solver.h"

solver::solver(){}
solver::solver(double DT, double TotalTime, std::vector<planet> Planets_List)
{
  dt = DT;
  totaltime = TotalTime;
  planet p1 = P1;
  planet p2 = P2;
  N = totaltime/dt + 1;
}

cube solver::solve_motion(void function)
{
  cube positional_tensor;
  positional_tensor = zeros<cube>(3,N,2);
  for (int t=0; t<N; t++){
    function(p1, p2, dt);
    positional_tensor[0,t,0] = p1.x;
    positional_tensor[1,t,0] = p1.y;
    positional_tensor[2,t,0] = p1.z;
    positional_tensor[0,t,1] = p2.x;
    positional_tensor[1,t,1] = p2.y;
    positional_tensor[2,t,1] = p2.z;
  }
  return positional_tensor
}
