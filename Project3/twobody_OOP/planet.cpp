#include "planet.h"

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
  acc_factor *= mass;
}

double planet::distance(const planet& otherplanet)
{
  double xdiff = x - otherplanet.x;
  double ydiff = y - otherplanet.y;
  double zdiff = z - otherplanet.z;
  return sqrt(xdiff*xdiff + ydiff*ydiff + zdiff*zdiff);
}

void planet::setName(string Name)
{
  name = Name;
}
