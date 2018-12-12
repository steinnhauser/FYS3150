#include "lithosphere.h"

void JacobiMethodLithosphere(int situation, string filename){
  /*
   * Solver throughout 1 Gyr of the lithosphere in three zones:
   * Zone 1: 0-20km,
   * Zone 2: 20-40km,
   * Zone 3: 40-120km.
   * Situation=1: no heat production
   * Situation=2: natural heat production
   * Situation=3: subduction: natural + extra heat production
   */

  // initialization
  int nx = 125; // 0-150 km wide
  int ny = 100; // 0-120 km deep
  int nt = 100; // number of time steps
  double dx = 0.01; // step length [1.2 km]: 0.01*[1.2 km]*100 points = 120 km
  double dt = 0.01; // 1 = [10^9 yr]: 100*dt = 1 Gyr

  // Initial conditions
  mat u = zeros<mat>(nx+1,ny+1); // Scaled from 0-1 -> 8-1300 deg Celsius
  // Linearly from 0-1 from depth 0-120 km
  for (double j=0; j<=ny; j++) {
    u(0,j) = (j/ny);
    u(nx,j) = (j/ny);
  }
  // u=1 at depth 120 km, u=0 at surface
  for (int i=0; i<=nx; i++) {
    u(i,ny) = 1;
  }
  mat u_old = u;

  // Constants and variables
  int maxiter = 20000; // No. of iterations each time step in Jacobi Method
  double delta, diff, Q, time;
  double scale = (nx+1)*(ny+1); // No. of points in matrix
  double tol = 1e-8; // tolerance for convergence in Jacobi method
  double alpha = dt/(dx*dx);
  double rho = 3.51*1e3; // density [1000 kg/m^3]
  double cp = 1000; // heat capacity [J/kg/deg Celsius]
  double k = 2.5; // thermal conductivity [W/m/deg Celsius]
  double uscale = 1292; // temperature scale
  double tscale = 3.1557e16; // time scale
  double xscale = 120000; // distance scale
  double eqScale = tscale*k/(rho*cp*xscale*xscale);
  double Qscale = tscale*dt/(rho*cp*uscale);
  double factor1 = eqScale*alpha;
  double factor2 = 1/(1 + 4*factor1);

  // Construction of Qvec: Q1, Q2 are doubles, Q3: Q3(natural) + Qtime(enrichment)
  // Natural heat production in zones:
  double Q1 = 1.4e-6*Qscale;
  double Q2 = 0.35e-6*Qscale;
  double Q3 = 0.05e-6*Qscale;
  vec Qvec = zeros<vec>(ny+1);
  for (int i=0; i<=16; i++) Qvec(i) = Q1; // 0-20 km depth
  for (int i=17; i<=33; i++) Qvec(i) = Q2; // 20-40 km depth
  for (int i=34; i<=ny; i++) Qvec(i) = Q3; // 40+ km depth

  // Extra enrichment due to subduction:
  vec Qtime = zeros<vec>(nt+1);
  double U_enrich, Th_enrich, K_enrich;
  for (int t=0; t<=nt; t++) {
    time = (double) t/nt;
    U_enrich = pow(0.5,time/4.47);
    Th_enrich = pow(0.5,time/14.0);
    K_enrich = pow(0.5,time/1.25);
    Q = 0.5*1e-6*(0.4*U_enrich + 0.4*Th_enrich + 0.2*K_enrich);
    Qtime(t) = Qscale*Q;
  }

  // time loop
  for (int t=1; t<=nt; t++)
  {
    int iter = 0;
    double diff=1;
    mat u_guess = u;
    while (iter < maxiter && diff > tol)
    {
      diff = 0;
      for (int j=1; j<ny; j++) {
        for (int i=1; i<nx; i++) {
          // Situation separation
          if (situation==1) {
            Q=0;
          } else {
            Q=Qvec(j);
          }
          if (j >= 34) Q += Qtime(t); // Zone 3: with extra enrichment
          // Jacobi method algorithm, u should converge towards solution
          delta = (u_guess(i,j+1)+u_guess(i,j-1)+u_guess(i+1,j)+u_guess(i-1,j));
          u(i,j) = factor2*(factor1*delta + Q + u_old(i,j));
          diff += fabs(u(i,j) - u_guess(i,j));
        }
      }
      u_guess = u;
      diff /= scale;
      iter++;
    } // end iteration loop
    u_old = u;
    cout << "timestep: " <<  t << " iterations: " << iter << endl;
  } // end time loop
  u.save("data/lithosphere_QR.bin", raw_binary);
}
