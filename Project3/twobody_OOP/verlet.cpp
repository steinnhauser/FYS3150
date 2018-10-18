#include "verlet.h"

void verlet_step(Body& p1, Body& p2, double dt)
{
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
  double hh_2 = dt*dt/2.0;
  double h_2 = dt/2.0;
  // update position using 2nd degree Taylor polynomial
  p1.x += dt*p1.vx + hh_2*x_acc_p1;
  p1.y += dt*p1.vy + hh_2*y_acc_p1;
  p1.z += dt*p1.vz + hh_2*z_acc_p1;
  p2.x += dt*p2.vx + hh_2*x_acc_p2;
  p2.y += dt*p2.vy + hh_2*y_acc_p2;
  p2.z += dt*p2.vz + hh_2*z_acc_p2;
  // find new accelerations
  double r_n = p1.distance(p2);
  double rrr_n = r_n*r_n*r_n;
  double acc_p1_n = p2.acc_factor/rrr_n;
  double acc_p2_n = p1.acc_factor/rrr_n;
  double x_acc_p1_n = (p1.x - p2.x)*acc_p1_n;
  double y_acc_p1_n = (p1.y - p2.y)*acc_p1_n;
  double z_acc_p1_n = (p1.z - p2.z)*acc_p1_n;
  double x_acc_p2_n = (p2.x - p1.x)*acc_p2_n;
  double y_acc_p2_n = (p2.y - p1.y)*acc_p2_n;
  double z_acc_p2_n = (p2.z - p1.z)*acc_p2_n;
  // update velocities
  p1.vx += (x_acc_p1_n + x_acc_p1)*h_2;
  p1.vy += (y_acc_p1_n + y_acc_p1)*h_2;
  p1.vz += (z_acc_p1_n + z_acc_p1)*h_2;
  p2.vx += (x_acc_p2_n + x_acc_p2)*h_2;
  p2.vy += (y_acc_p2_n + y_acc_p2)*h_2;
  p2.vz += (z_acc_p2_n + z_acc_p2)*h_2;
}
