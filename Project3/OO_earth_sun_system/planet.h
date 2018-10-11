#ifndef PLANET_H
#define PLANET_H
#include <armadillo>

class planet
{
public:
  // initial values
  double x;
  double y;
  double z;
  double xv;
  double yv;
  double zv;
  double Fx;
  double Fy;
  double Fz;
  double mass;

  // constructor
  planet();
  planet(x, y, z, xv, yv, zv, mass);

  // functions
  double distance(planet otherplanet);
  double acceleration(planet otherplanet, G_constant);

  kin_energy();
  pot_energy();
};

#endif // PLANET_H
