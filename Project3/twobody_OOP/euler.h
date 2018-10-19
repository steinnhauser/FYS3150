#ifndef EULER_H
#define EULER_H
#include <armadillo>
#include <math.h>
#include <iostream>
#include "body.h"
using namespace arma;

void euler_step(Body& p1, Body& p2, double dt);

#endif // EULER_H
