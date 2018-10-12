#include "planet.h"
#include <cmath>

planet::planet(){}
planet::planet(double mass, double x, double y, double z, double vx, double vy, double vz)
{
  this->mass = mass;
  this->x = x;
  this->y = y;
  this->z = z;
  this->vx = vx;
  this->vy = vy;
  this->vz = vz;
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
