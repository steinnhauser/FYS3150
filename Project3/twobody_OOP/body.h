#ifndef BODY_H
#define BODY_H
#include <armadillo>
#include <math.h> // for M_PI
#include <string>
#include <iostream>
#include <cmath>

using namespace std;
using namespace arma;

class Body
{
public:
  // initial values
  double x;
  double y;
  double z;
  double vx;
  double vy;
  double vz;
  double mass;
  double acc_factor;

  // constructor
  Body();
  Body(double Mass, double X, double Y, double Z, double VX, double VY, double VZ);

  // functions
  double distance(const Body& otherbody);
};

#endif // BODY_H
