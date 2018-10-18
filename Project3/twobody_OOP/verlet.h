#ifndef VERLET_H
#define VERLET_H
#include <armadillo>
#include <math.h>
#include "body.h"
using namespace arma;

void verlet_step(Body& p1, Body& p2, double dt);

#endif // VERLET_H
