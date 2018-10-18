#ifndef INTEGRATOR_H
#define INTEGRATOR_H
#include <armadillo>
#include <vector>
#include <cmath>
#include "body.h"
#include "euler.h"
#include "verlet.h"

using namespace arma;

class Integrator
{
public:
  // initial values
  double dt;
  double totaltime;
  int N;
  body p1;
  body p2;

  // constructor
  Integrator();
  Integrator(double DT, double TotalTime, body P1, body P2);

  // functions
  cube solve_motion(void method);
};

#endif // INTEGRATOR_H
