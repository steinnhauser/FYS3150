#include <planet.h>
#include <cmath>
#include <math.h>

//functions
double planet::distance(const planet& otherplanet) {
  double xdiff = x - otherplanet.x;
  double ydiff = y - otherplanet.y;
  double zdiff = z - otherplanet.z;
  return sqrt(xdiff*xdiff + ydiff*ydiff + zdiff*zdiff);
}


double planet::acceleration(double r, const planet& otherplanet) {
  return grav * otherplanet.mass / (r*r);
}
// and so on...
