#include "lithosphere.h"


void JacobiMethodLithosphere(){
  /*
   * Iterative solver for a of a diagonally dominant system og linear equations.
   */
  // initialization
  int nx = 150;
  int ny = 120;
  int nt = 10000;
  double dx = 1;
  double dt = 0.0001;

  // Initial conditions
  mat u = zeros<mat>(nx+1,ny+1);
  for (double i=0; i<=nx; i++) {
    for (double j=0; j<=ny; j++) {
      u(i,j) = 8 + (j/ny)*1292;
    }
  }
  mat u_old = u;

  // mat u_guess = zeros<mat>(nx+1,nx+1);
  int maxiter = 1000;
  double delta, tol=1e-14;
  double alpha = dt/(dx*dx);
  double rho = 3.51*3.51*3.51;
  double cp = 1000;
  double k = 2.5;
  double factor = 1.0/(1.0 + 4*alpha);
  double factor_a = alpha*factor*k/(rho*cp);
  double Q1 = 1.4e-6*dt;
  double Q2 = 0.35e-6*dt;
  double Q3 = 0.05e-6*dt;
  double scale = (nx+1)*(ny+1);
  string fn_base = "data/lithosphere/u";
  string filename;
  string fn_end = ".bin";
  // time loop
  for (int t=1; t<=nt; t++)
  {
    int iter = 0;
    double diff=1;
    mat u_guess = ones<mat>(nx+1,nx+1);
    while (iter < maxiter && diff > tol)
    {
      diff = 0;
      // Loop over upper Crust
      for (int j=1; j<20; j++) {
        for (int i=1; i<nx; i++) {
          // u_guess is the previous u, which also work for a random guess
          delta = (u_guess(i,j+1)+u_guess(i,j-1)+u_guess(i+1,j)+u_guess(i-1,j));
          u(i,j) = factor_a*delta + factor*(u_old(i,j) - Q1);
          diff += fabs(u(i,j) - u_guess(i,j));
        }
      }
      // Loop over middle part
      for (int j=20; j<40; j++) {
        for (int i=1; i<nx; i++) {
          // u_guess is the previous u, which also work for a random guess
          delta = (u_guess(i,j+1)+u_guess(i,j-1)+u_guess(i+1,j)+u_guess(i-1,j));
          u(i,j) = factor_a*delta + factor*(u_old(i,j) - Q2);
          diff += fabs(u(i,j) - u_guess(i,j));
        }
      }
      // Loop over Mantle
      for (int j=40; j<ny; j++) {
        for (int i=1; i<nx; i++) {
          // u_guess is the previous u, which also work for a random guess
          delta = (u_guess(i,j+1)+u_guess(i,j-1)+u_guess(i+1,j)+u_guess(i-1,j));
          u(i,j) = factor_a*delta + factor*(u_old(i,j) - Q3);
          diff += fabs(u(i,j) - u_guess(i,j));
        }
      }
      u_guess = u;
      diff /= scale;
      iter++;
    } // end iteration loop
    filename = fn_base + to_string(t) + fn_end;
    u_old = u;
    u.save(filename, raw_binary);
    cout << "timestep: "<<  t << " iterations: " << iter << endl;
  } // end time loop
}
