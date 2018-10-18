#ifndef VERLET_METHOD_H
#define VERLET_METHOD_H
#include <armadillo>
#include <math.h>
using namespace arma;

void verlet_method_step(planet& p1, planet& p2, double dt);

#endif // VERLET_METHOD_H
