#ifndef EULER_H
#define EULER_H
#include <armadillo>
#include <math.h>
#include "body.h"
using namespace arma;

void euler_step(body& p1, body& p2, double dt);

#endif // EULER_H
