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
  const double grav = 4*M_PI*M_PI;

  // constructor
  planet();
  planet(x, y, z, vx, vy, vz, mass);

  // functions
  double distance(planet otherplanet);
  double acceleration(planet otherplanet, G_constant);

  // kin_energy();
  // pot_energy();
};

#endif // PLANET_H
