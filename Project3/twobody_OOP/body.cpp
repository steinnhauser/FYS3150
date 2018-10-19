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
  acc_factor = 4*M_PI*M_PI*mass;
}

double Body::distance(const Body& otherbody)
{
  double xdiff = x - otherbody.x;
  double ydiff = y - otherbody.y;
  double zdiff = z - otherbody.z;
  return sqrt(xdiff*xdiff + ydiff*ydiff + zdiff*zdiff);
}
