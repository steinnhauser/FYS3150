#ifndef BODY_H
#define BODY_H
#include <armadillo>
#include <math.h> // for M_PI
#include <string>
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
  double acc_factor = 4*M_PI*M_PI
  string name;

  // constructor
  body();
  body(double Mass, double X, double Y, double Z, double VX, double VY, double VZ);

  // functions
  double distance(const body& otherbody);
  void setName(string Name);
};

#endif // BODY_H
