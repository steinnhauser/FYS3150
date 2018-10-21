#include <iostream>
#include <string>
#include <armadillo>
#include <iomanip>
#include <cmath>
#include <math.h>
#include <vector>
#include <fstream>

using namespace std;
using namespace arma;

void velocity_verlet_solve(double dt, double T, string filename, bool general_relativity);

int main(int argc, char* argv[]) {
  /*
  Units used:
  1 unit of time = 1 yr
  1 unit of length = 1 AU
  1 unit of velocity = 1 AU/yr
  */
  double T = 100;
  double dt = 0.000001;

  velocity_verlet_solve(dt,T,"./data/mercury.txt",false);
  velocity_verlet_solve(dt,T,"./data/mercury_GR.txt",true);
  return 0;
}

void velocity_verlet_solve(double dt, double T, string filename, bool general_relativity) {
  double x0 = 0.3075;
  double y0 = 0;
  double vx = 0;
  double vy = 12.44;
  double hh_2 = dt*dt/2.0;
  double h_2 = dt/2.0;
  double g_mass_sun = 4*M_PI*M_PI;
  double cc = 3999262982.4989; // AU^2/year^2
  double ax,ay,ax_new,ay_new,l,G;
  double GR = 1;
  int N = T/dt;
  int t_old;
  vec time_vec = linspace<vec>(0,T,N);
  vec x = zeros<vec>(N); x(0) = x0;
  vec y = zeros<vec>(N); y(0) = y0;
  vec r = zeros<vec>(N); r(0) = sqrt(x0*x0 + y0*y0);

  for (int t=1; t<N; t++) {
    r(t) = sqrt(x(t)*x(t) + y(t)*y(t));

    t_old = t-1;
    if (general_relativity) {
      l = x(t_old)*vy - y(t_old)*vx;
      GR += 3*l*l/(cc*r(t_old)*r(t_old));
    }
    G = - GR*g_mass_sun/(r(t_old)*r(t_old)*r(t_old));
    ax = x(t)*G;
    ay = y(t)*G;
    x(t) = x(t_old) + dt*vx + hh_2*ax;
    y(t) = y(t_old) + dt*vy + hh_2*ay;

    if (general_relativity) {
      l = x(t)*vy - y(t)*vx;
      GR += 3*l*l/(cc*r(t)*r(t));
    }
    G = - GR*g_mass_sun/(r(t)*r(t)*r(t));
    ax_new = x(t)*G;
    ay_new = y(t)*G;
    vx += h_2*(ax + ax_new);
    vy += h_2*(ay + ay_new);
  }

  ofstream ofile1;
  ofile1.open("positions.txt", ofstream::out | ofstream::trunc);
  for(int i=0; i<N; i++) {
    ofile1 << setw(15) << setprecision(10) << x(i);
    ofile1 << setw(15) << setprecision(10) << y(i) << endl;
  }
  ofile1.close();

  double rad_2_arcsec = 180*3600/M_PI;
  vector<double> times;
  vector<double> angles;
  for (int i=1; i<N-1; i++) {
    if (r(i) < r(i-1) && r(i) < r(i+1)) {
      angles.push_back(atan(y(i)/x(i))*rad_2_arcsec);
      times.push_back(time_vec(i));
    }
  }
  ofstream ofile;
  ofile.open(filename, ofstream::out | ofstream::trunc);
  double n = angles.size();
  cout << "perihelion events found during " << T << " years: " << n << endl;
  for(int i=0; i<n; i++) {
    ofile << setw(15) << setprecision(10) << times[i];
    ofile << setw(15) << setprecision(10) << angles[i] << endl;
  }
  ofile.close();
}
