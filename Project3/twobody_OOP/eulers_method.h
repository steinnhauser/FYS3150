#ifndef EULERS_METHOD_H
#define EULERS_METHOD_H
#include <armadillo>
#include <math.h>
using namespace arma;

void eulers_method_step(planet& p1, planet& p2, double dt);

#endif // EULERS_METHOD_H
