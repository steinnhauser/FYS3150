#include "functions.h"

void explicitForwardEuler() {
  // Solves position in 1D for all times using the explicit forward Euler scheme

  // initialization
  int i,t;
  int nt = 100; // number of time steps
  int nx = 100; // number of position steps
  double dx = 0.01;
  double dt = 0.00005;
  double alpha = dt/dx/dx;
  double beta = (1 + 2*alpha);
  int L = nx - 1;
  mat u = zeros<mat>(nx,nt);

  // boundary conditions, [u(x,0)=0 and u(0,t)=0]
  for (t=0; t<nt; t++) u(L,t) = 1;

  // time loop
  for (t=1; t<nt; t++) {
    tp = t-1; // previous time step
    for (i=1; i<L; i++) { // inner time points
      u(i,t) = alpha*(u(i-1,tp) + u(i+1,tp)) + beta*u(i,tp);
    }
  }
  // call write to file function
}

void implicitBackwardEuler() {
  // Solves position in 1D for all times using the explicit forward Euler scheme

  // initialization
  int i,t;
  int nt = 100; // number of time steps
  int nx = 100; // number of position steps
  double dx = 0.01;
  double dt = 0.00005;
  double alpha = dt/dx/dx;
  double beta = (1 + 2*alpha);
  int L = nx - 1;
  mat u = zeros<mat>(nx,nt);

  // boundary conditions, [u(x,0)=0 and u(0,t)=0]
  for (t=0; t<nt; t++) u(L,t) = 1;

  // time loop
  for (t=0; t<nt; t++) {
    tn = t+1; // next time step
    for (i=1; i<L; i++) { // inner time points
      u(i,t) = tridiagonalSolver(-alpha, beta, nx, u(i-1,t));
    }
  }
}

void CrankNicolsonScheme() {

}

vec tridiagonalSolver(double d, double e, int n) {
  /*
   * Thomas algorithm:
   * Solves matrix vector equation A*u_old = u_new,
   * for A being a tridiagonal matrix with constant
   * elements d on main diagonal and e on the off diagonals.
   */
  vec beta = zeros<vec>(n); // temporary storage vector for forw/backw substitution
  vec u_new = zeros<vec>(n); u_new[1] = u_old[1]/d;
  double btemp = d; int i;

  // forward substitution
  for(i=2; i<n; i++){
    beta[i] = e/btemp;
    btemp = d - e*beta[i];
    u_new[i] = (u_old[i] - e*u_new[i-1])/btemp;
  }
  // backward substitution
  for(i=n-1; i>0; i--){
    u_new[i] -= beta[i+1]*u_new[i+1];
  }
  return u_new;
}
