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
  Body p1;
  Body p2;

  // constructor
  Integrator();
  Integrator(Body P1, Body P2);

  // functions
  cube solve_motion(double dt, double totaltime, void (*method)(double, Body, Body));
};

#endif // INTEGRATOR_H
