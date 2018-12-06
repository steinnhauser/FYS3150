#include "functions.h"

void explicitForwardEuler() {
  // Solves position in 1D for all times using the explicit forward Euler scheme

  // initialization
  int i,t,tp;
  int nt = 100000; // number of time steps
  int nx = 100; // number of position steps
  double dx = 0.01;
  double dt = 0.00001;
  double alpha = dt/dx/dx;
  double beta = (1 - 2*alpha);
  mat u = zeros<mat>(nx+1,nt+1);

  // boundary conditions, [u(x,0)=0 and u(0,t)=0]
  for (t=0; t<=nt; t++) u(nx,t) = 1;

  // time loop
  for (t=1; t<=nt; t++) {
    tp = t-1; // previous time step
    for (i=1; i<nx; i++) { // inner time points
      u(i,t) = alpha*(u(i-1,tp) + u(i+1,tp)) + beta*u(i,tp);
    }
  }
  // call write to file function
  string filename = "data/explicit.bin";
  writeMatrixFile(filename, u);
}

void implicitBackwardEuler() {
  // Solves position in 1D for all times using the explicit forward Euler scheme

  // initialization
  int i,t,tn;
  int nt = 10000; // number of time steps
  int nx = 1000; // number of position steps
  double dx = 0.001;
  double dt = 0.001;
  double alpha = dt/dx/dx;
  double beta = (1 + 2*alpha);
  alpha *= -1;
  mat u = zeros<mat>(nx+1,nt+1);

  // boundary conditions, [u(x,0)=0 and u(0,t)=0]
  for (t=0; t<=nt; t++) u(nx,t) = 1;

  // time loop
  for (t=1; t<=nt; t++) {
    tridiagonalSolver(u, beta, alpha, nx, t);
    u(nx,t) = 1;
  }

  string filename = "data/implicit.bin";
  writeMatrixFile(filename, u);
}

void CrankNicolsonScheme() {
  // call a combination of explicit and implicit. "First use explicit, then
  // Thomas algorithm on the explicit solution." -Alexander Sexton, 2018

  // initialization
  int i,t,tn,tp;
  int nt = 100; // number of time steps
  int nx = 100; // number of position steps
  double dx = 0.01;
  double dt = 0.00001;
  double alpha1 = dt/dx/dx;
  double beta1 = (1 - 2*alpha1); // explicit beta
  double beta2 = (1 + 2*alpha1); // implicit beta
  double alpha2 = -alpha1;
  mat u = zeros<mat>(nx+1,nt+1);

  // boundary conditions, [u(x,0)=0 and u(0,t)=0]
  for (t=0; t<=nt; t++) u(nx,t) = 1;
  // time loop
  for (t=1; t<=nt; t++) {
    // Explicit
    tp = t-1; // previous time step
    for (i=1; i<nx; i++) { // inner time points
      u(i,t) = 0.5*(alpha1*(u(i-1,tp) + u(i+1,tp)) + beta1*u(i,tp));
    }
    // Implicit
    tridiagonalSolver(u, beta2, alpha2, nx, t);
    u(nx,t) = 1;
  }

  string filename = "data/CrankNicolson.bin";
  writeMatrixFile(filename, u);
}

void tridiagonalSolver(mat& u, double d, double e, int n, int t_new) {
  /*
   * Thomas algorithm:
   * Solves matrix vector equation u_old = A*u_new,
   * for A being a tridiagonal matrix with constant
   * elements d on main diagonal and e on the off diagonals.
   */
  vec beta = zeros<vec>(n+1); // temporary storage vector for forw/backw substitution
  int t_old = t_new - 1;
  u(1,t_new) = u(1,t_old)/d;
  double btemp = d; // temporary storage double

  // forward substitution
  for(int i=2; i<=n; i++){
    beta(i) = e/btemp;
    btemp = d - e*beta(i);
    u(i,t_new) = (u(i,t_old) - e*u(i-1,t_new))/btemp;
  }

  // backward substitution
  for(int i=n-1; i>0; i--){
    u(i,t_new) -= beta(i+1)*u(i+1,t_new);
  }
}

void JacobiMethod(){
  /*
   * Iterative solver for a of a diagonally dominant system og linear equations.
   */
  // initialization
  int nx = 200;
  int nt = 30;
  double dx = 0.01;
  double dt = 0.001;

  // Initial conditions
  cube u = zeros<cube>(nx+1,nx+1,nt+1);
  for (int t=0; t<=nt; t++) {
    for (int i=0; i<=nx; i++) {
      u(i,0,t) = 1;
      u(0,i,t) = 1;
      u(i,nx,t) = 1;
      u(nx,i,t) = 1;
    }
  }

  // mat u_guess = zeros<mat>(nx+1,nx+1);
  int maxiter = 100000;
  double delta, tol=0.0001;
  double alpha = dt/(dx*dx);
  double factor = 1/(1 + 4*alpha);
  double factor_a = alpha*factor;
  double scale = nx*nx;

  // time loop
  for (double t=1; t<=nt; t++)
  {
    int iter = 0;
    double diff=1;
    mat u_guess = ones<mat>(nx+1,nx+1);
    while (iter < maxiter && diff > tol)
    {
      diff = 0;
      // Loop over all inner elements, will converge towards solution
      for (int j=1; j<nx; j++) {
        for (int i=1; i<nx; i++) {
          delta = (u_guess(i,j+1)+u_guess(i,j-1)+u_guess(i+1,j)+u_guess(i-1,j));
          u(i,j,t) = factor_a*delta + factor*u(i,j,t-1);
          diff += fabs(u(i,j,t) - u_guess(i,j));
        }
      } // end of double for loop
      u_guess = u.slice(t);
      diff /= scale;
      iter++;
    } // end iteration loop
  } // end time loop

  u.resize(size(u));
  string filename = "data/twodimensions.bin";
  u.save(filename,raw_binary);
  ofstream ofile;
  ofile.open("data/twodimensions.txt");
  ofile << nx << endl;
  ofile << nt << endl;
  ofile.close();

}

void writeMatrixFile(string filename, mat u){
  bool saved = u.save(filename, raw_binary);
  if (saved) {cout << "File " << filename << " written." << "\n";}
  else {cout << "Error in saving file." << "\n";}
}
