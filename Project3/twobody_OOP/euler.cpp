#include "euler.h"

void euler_step(Body& p1, Body& p2, double dt)
{
  cout << p1.x << " " << p2.x << endl;
  double r = p1.distance(p2);
  double rrr = r*r*r;
  double acc_p1 = p2.acc_factor/rrr;
  double acc_p2 = p1.acc_factor/rrr;
  // find acceleration on both objects in x,y,z-direction
  double x_acc_p1 = (p1.x - p2.x)*acc_p1;
  double y_acc_p1 = (p1.y - p2.y)*acc_p1;
  double z_acc_p1 = (p1.z - p2.z)*acc_p1;
  double x_acc_p2 = (p2.x - p1.x)*acc_p2;
  double y_acc_p2 = (p2.y - p1.y)*acc_p2;
  double z_acc_p2 = (p2.z - p1.z)*acc_p2;
  // update velocities
  p1.vx += x_acc_p1*dt;
  p1.vy += y_acc_p1*dt;
  p1.vz += z_acc_p1*dt;
  p2.vx += x_acc_p2*dt;
  p2.vy += y_acc_p2*dt;
  p2.vz += z_acc_p2*dt;
  // update positions
  p1.x += p1.vx*dt;
  p1.y += p1.vy*dt;
  p1.z += p1.vz*dt;
  p2.x += p2.vx*dt;
  p2.y += p2.vy*dt;
  p2.z += p2.vz*dt;
}
