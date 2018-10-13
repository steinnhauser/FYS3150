#ifndef PLANET_H
#define PLANET_H
#include <armadillo>
#include <math.h> // for M_PI
#include <string>
#include <cmath>

using namespace std;

class planet
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
  double gravity_factor = 4*M_PI*M_PI;
  string name;

  // constructor
  planet();
  planet(double Mass, double X, double Y, double Z, double VX, double VY, double VZ);

  // functions
  double distance(const planet& otherplanet);
  double acceleration(double r, const planet& otherplanet);

  void setName(string Name);

  // kin_energy();
  // pot_energy();
};

#endif // PLANET_H
