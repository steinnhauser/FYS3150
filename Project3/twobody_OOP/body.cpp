#include "body.h"

Body::Body(){}
Body::Body(double Mass, double X, double Y, double Z, double VX, double VY, double VZ)
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

double Body::distance(const body& otherbody)
{
  double xdiff = x - otherbody.x;
  double ydiff = y - otherbody.y;
  double zdiff = z - otherbody.z;
  return sqrt(xdiff*xdiff + ydiff*ydiff + zdiff*zdiff);
}

void Body::setName(string Name)
{
  name = Name;
}
