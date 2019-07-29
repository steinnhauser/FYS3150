#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <math.h>
#include <vector>
#include <fstream>

using namespace std;

int main() {
  /*
  Units used:
  1 unit of time = 1 yr
  1 unit of length = 1 AU
  1 unit of velocity = 1 AU/yr
  */
  double T = 100;
  double dt = 1e-7;
  double x0 = 0.3075;
  double y0 = 0;
  double vx = 0;
  double vy = 12.44;
  double hh_2 = dt*dt/2.0;
  double h_2 = dt/2.0;
  double g_mass_sun = 4*M_PI*M_PI;
  double c = 63239.7263; // au/year
  double cc = c*c;
  double ax,ay,ax_new,ay_new,l,G,GR,x_new,y_new,r;
  double x_old = x0;
  double y_old = y0;
  double rad_2_arcsec = 180*3600/M_PI;
  double rpp = sqrt(x0*x0 + y0*y0);
  double rp = rpp;
  double elapsed_time = 0;
  vector<double> times;
  vector<double> angles;

  while (elapsed_time < T) {
    l = x_old*vy - y_old*vx; // angular momentum/mass: r x v
    GR = 1 + 3*l*l/(cc*rp*rp); // Force contribution from general relativity
    G = - GR*g_mass_sun/(rp*rp*rp); // total gravity_force/r
    ax = x_old*G;
    ay = y_old*G;
    // update positions
    x_new = x_old + dt*vx + hh_2*ax;
    y_new = y_old + dt*vy + hh_2*ay;
    r = sqrt(x_new*x_new + y_new*y_new);
    l = x_new*vy - y_new*vx; // angular momentum/mass: r x v
    GR = 1 + 3*l*l/(cc*r*r); // Force contribution from general relativity
    G = - GR*g_mass_sun/(r*r*r); // total gravity_force/r
    ax_new = x_new*G;
    ay_new = y_new*G;
    // update velocities
    vx += h_2*(ax + ax_new);
    vy += h_2*(ay + ay_new);
    // check if perihelion
    if (rp < r && rp < rpp) {
      angles.push_back(atan(y_old/x_old)*rad_2_arcsec);
      times.push_back(elapsed_time);
    }
    // update of temporary variables
    x_old = x_new;
    y_old = y_new;
    rpp = rp;
    rp = r;
    elapsed_time += dt;
  }
  // write file with columns: time angle (at perihelion events)
  ofstream ofile;
  ofile.open("./mercury.txt", ofstream::out | ofstream::trunc);
  double n = angles.size();
  cout << "perihelion events found during " << T << " years: " << n << endl;
  for(int i=0; i<n; i++) {
    ofile << setw(20) << setprecision(10) << times[i];
    ofile << setw(20) << setprecision(10) << angles[i] << endl;
  }
  ofile.close();
  return 0;
}
