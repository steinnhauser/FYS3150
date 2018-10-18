#include "verlet_method.h"

void verlet_method_step(planet& p1, planet& p2, double dt)
{
  double r = p1.distance(p2);
  double rrr = r*r*r;
  double acc_p1 = p2.acc_factor/rrr;
  double acc_p2 = p1.acc_factor/rrr;
  // find acceleration on both objects in x,y,z-direction
  x_acc_p1 = (p1.x - p2.x)*acc_p1;
  y_acc_p1 = (p1.y - p2.y)*acc_p1;
  z_acc_p1 = (p1.z - p2.z)*acc_p1;
  x_acc_p2 = (p2.x - p1.x)*acc_p2;
  y_acc_p2 = (p2.y - p1.y)*acc_p2;
  z_acc_p2 = (p2.z - p1.z)*acc_p2;
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
  double r = p1.distance(p2);
  double rrr = r*r*r;
  double acc_p1 = G*p2.mass/rrr;
  double acc_p2 = G*p1.mass/rrr;
  x_acc_p1_n = (p1.x - p2.x)*acc_p1;
  y_acc_p1_n = (p1.y - p2.y)*acc_p1;
  z_acc_p1_n = (p1.z - p2.z)*acc_p1;
  x_acc_p2_n = (p2.x - p1.x)*acc_p2;
  y_acc_p2_n = (p2.y - p1.y)*acc_p2;
  z_acc_p2_n = (p2.z - p1.z)*acc_p2;
  // update velocities
  p1.vx += (x_acc_p1_n + x_acc_p1)*h_2;
  p1.vy += (y_acc_p1_n + y_acc_p1)*h_2;
  p1.vz += (z_acc_p1_n + z_acc_p1)*h_2;
  p2.vx += (x_acc_p2_n + x_acc_p2)*h_2;
  p2.vy += (y_acc_p2_n + y_acc_p2)*h_2;
  p2.vz += (z_acc_p2_n + z_acc_p2)*h_2;
}
