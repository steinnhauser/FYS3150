#include "planet.h"
#include <cmath>

planet::planet(){}
planet::planet(double Mass, double X, double Y, double Z, double VX, double VY, double VZ)
{
  mass = Mass;
  x = X;
  y = Y;
  z = Z;
  vx = VX;
  vy = VY;
  vz = VZ;
}

double planet::distance(const planet& otherplanet) {
  double xdiff = x - otherplanet.x;
  double ydiff = y - otherplanet.y;
  double zdiff = z - otherplanet.z;
  return sqrt(xdiff*xdiff + ydiff*ydiff + zdiff*zdiff);
}

double planet::acceleration(double r, const planet& otherplanet) {
  return - gravity_factor * otherplanet.mass / (r*r);
}

void planet::setName(string Name)
{
  name = Name;
}
