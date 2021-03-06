#include "eulers_method.h"

void eulers_method_calculate(double x0, double y0, double z0, double xv0, double yv0, double zv0, int N, double dt,
  vec& x_pos, vec& y_pos, vec& z_pos, vec& kin_energy, vec& pot_energy, vec& ang_mom)
{
  const double G_MassSun = 4*M_PI*M_PI; // [AU^3/yr^2]
  vec x_vel = zeros<vec>(N);
  vec y_vel = zeros<vec>(N);
  vec z_vel = zeros<vec>(N);
  x_pos(0) = x0;
  y_pos(0) = y0;
  y_pos(0) = z0;
  x_vel(0) = xv0;
  y_vel(0) = yv0;
  z_vel(0) = zv0;

  double x_acc, y_acc, z_acc; // accelerations
  double r_squared, factor, c1, c2, c3; // will be updated each iteration for less FLOPS
  clock_t start, finish;
  start = clock();
  for (int i=0; i<(N-1); i++) {
    r_squared = x_pos(i)*x_pos(i) + y_pos(i)*y_pos(i) + z_pos(i)*z_pos(i);
    factor = - G_MassSun*dt/(pow(r_squared, 1.5));
    x_acc = x_pos(i) * factor;
    y_acc = y_pos(i) * factor;
    z_acc = z_pos(i) * factor;
    x_vel(i+1) = x_vel(i) + x_acc;
    y_vel(i+1) = y_vel(i) + y_acc;
    z_vel(i+1) = z_vel(i) + z_acc;
    x_pos(i+1) = x_pos(i) + dt*x_vel(i);
    y_pos(i+1) = y_pos(i) + dt*y_vel(i);
    z_pos(i+1) = z_pos(i) + dt*z_vel(i);

    kin_energy(i) = 0.5*(x_vel(i)*x_vel(i) + y_vel(i)*y_vel(i) + z_vel(i)*z_vel(i)); // except mass
    pot_energy(i) = - G_MassSun/(sqrt(r_squared)); // except mass
    c1 = y_pos(i)*z_vel(i) - z_pos(i)*y_vel(i);
    c2 = z_pos(i)*x_vel(i) - x_pos(i)*z_vel(i);
    c3 = x_pos(i)*y_vel(i) - y_pos(i)*x_vel(i);
    ang_mom(i) = sqrt(c1*c1 + c2*c2 + c3*c3); // except mass
  }
  finish = clock();
  // last value for energies and angular momentum:
  kin_energy(N-1) = 0.5*(x_vel(N-1)*x_vel(N-1) + y_vel(N-1)*y_vel(N-1) + z_vel(N-1)*z_vel(N-1)); // except mass
  pot_energy(N-1) = - G_MassSun/(sqrt(r_squared));
  c1 = y_pos(N-1)*z_vel(N-1) - z_pos(N-1)*y_vel(N-1);
  c2 = z_pos(N-1)*x_vel(N-1) - x_pos(N-1)*z_vel(N-1);
  c3 = x_pos(N-1)*y_vel(N-1) - y_pos(N-1)*x_vel(N-1);
  ang_mom(N-1) = sqrt(c1*c1 + c2*c2 + c3*c3);
  double looptime = (finish - start)*1.0/CLOCKS_PER_SEC*1000;
  cout << "Eulers method calculation complete, time: " << looptime << " ms" << endl;
}
