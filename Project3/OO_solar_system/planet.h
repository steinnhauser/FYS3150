#ifndef PLANET_H
#define PLANET_H
#include <armadillo>
#include <math.h> // for M_PI

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
  const double mass;
  const double gravity_factor = 4*M_PI*M_PI;

  // constructor
  planet(double x, double y, double z, double vx, double vy, double vz, const double mass);

  // functions
  double distance(const planet& otherplanet);
  double acceleration(double r, const planet& otherplanet);

  // kin_energy();
  // pot_energy();
};

#endif // PLANET_H
