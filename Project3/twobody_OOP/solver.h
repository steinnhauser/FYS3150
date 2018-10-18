#ifndef SOLVER_H
#define SOLVER_H
#include <armadillo>
#include <vector>
#include <cmath>
#include "planet.h"
#include "eulers_method.h"
#include "verlet_method.h"

using namespace arma;

class solver
{
public:
  // initial values
  double dt;
  double totaltime;
  int N;
  planet p1;
  planet p2;

  // constructor
  solver();
  solver(double DT, double TotalTime, planet P1, planet P2);

  // functions
  cube solve_motion(void method);
};

#endif // SOLVER_H
