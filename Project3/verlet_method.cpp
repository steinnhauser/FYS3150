#include <armadillo>
#include <iostream>
#include "verlet_method.h"

using namespace arma;
using namespace std;
//Method to calculate the VELOCITY VERLET
//This Verlet method is chosen since it conserves the energy and angular momentum of the planets.
vec verlet_method_calculate(double x0, double y0, double z0, double xv0, double yv0, double zv0, int N, double dt,
  vec& x_pos, vec& y_pos, vec& z_pos)
{
  const double G_MassSun = 4*M_PI*M_PI; //This has units AU^3/year^2
  vec x_vel = zeros<vec>(N);
  vec y_vel = zeros<vec>(N);
  vec z_vel = zeros<vec>(N);
  x_pos(0) = x0;
  y_pos(0) = y0;
  z_pos(0) = z0;
  x_vel(0) = xv0;
  y_vel(0) = yv0;
  z_vel(0) = zv0;

  double x_acc, y_acc, z_acc;
  double x_acc_new, y_acc_new, z_acc_new;
  double r_squared, factor1;
  double factor2 = dt*dt/2.0;
  double factor3 = dt/2.0;

  for (int i=0; i<(N-1); i++) {
    // Calculate the new positions using the current velocity and acceleration
    r_squared = x_pos(i)*x_pos(i) + y_pos(i)*y_pos(i) + z_pos(i)*z_pos(i);
    factor1 = - G_MassSun/(pow(r_squared, 1.5));
    x_acc = x_pos(i) * factor1;
    y_acc = y_pos(i) * factor1;
    z_acc = z_pos(i) * factor1;

    // Taylor approx for position step i+1:
    x_pos(i+1) = x_pos(i) + dt*x_vel(i) + factor2*x_acc;
    y_pos(i+1) = y_pos(i) + dt*y_vel(i) + factor2*y_acc;
    z_pos(i+1) = z_pos(i) + dt*z_vel(i) + factor2*z_acc;

    //Calculate the velocities using the next acceleration point r(i+1)=r_New
    r_squared = x_pos(i+1)*x_pos(i+1) + y_pos(i+1)*y_pos(i+1) + z_pos(i+1)*z_pos(i+1); // new r_squared
    factor1 = - G_MassSun/(pow(r_squared, 1.5));
    x_acc_new = x_pos(i+1) * factor1;
    y_acc_new = y_pos(i+1) * factor1;
    z_acc_new = z_pos(i+1) * factor1;

    x_vel(i+1) = x_vel(i) + factor3*(x_acc + x_acc_new);
    y_vel(i+1) = y_vel(i) + factor3*(y_acc + y_acc_new);
    z_vel(i+1) = z_vel(i) + factor3*(z_acc + z_acc_new);
  }
  cout << "Velocity Verlet calculation complete." << endl;
}
