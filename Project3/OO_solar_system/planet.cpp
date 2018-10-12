#include "planet.h"
#include <cmath>

double planet::distance(const planet& otherplanet) {
  double xdiff = x - otherplanet.x;
  double ydiff = y - otherplanet.y;
  double zdiff = z - otherplanet.z;
  return sqrt(xdiff*xdiff + ydiff*ydiff + zdiff*zdiff);
}

double planet::acceleration(double r, const planet& otherplanet) {
  return - gravity_factor * otherplanet.mass / (r*r);
}
