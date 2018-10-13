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
}

double planet::distance(const planet& otherplanet)
{
  double xdiff = x - otherplanet.x;
  double ydiff = y - otherplanet.y;
  double zdiff = z - otherplanet.z;
  return sqrt(xdiff*xdiff + ydiff*ydiff + zdiff*zdiff);
}

vec planet::acceleration(double r, const planet& otherplanet)
{
  double G = - gravity_factor * otherplanet.mass / (r*r*r);
  vec acc = zeros<vec>(3);
  // treat other planet as origin, to find x, y and z component: i.e. (x/r * G)
  acc[0] = (x - otherplanet.x)*G;
  acc[1] = (y - otherplanet.y)*G;
  acc[2] = (z - otherplanet.z)*G;
  return acc;
}

double planet::potential_energy(double r, const planet& otherplanet)
{
  return - gravity_factor * otherplanet.mass / r;
}

double planet::kinetic_energy()
{
  double vtot = sqrt(vx*vx + vy*vy + vz*vz);
  return 0.5*mass*vtot*vtot;
}


void planet::setName(string Name)
{
  name = Name;
}
