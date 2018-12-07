#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <armadillo>
#include <string>
#include <fstream>
#include <iomanip>
#include <math.h>

using namespace arma;
using namespace std;

void analytic1D(int nx, int nt, double dx, double dt, string filename);
void analytic2D(int nx, double dx, double t, double dt, string filename);
void explicitForwardEuler(int nx, int nt, double dx, double dt, string filename);
void implicitBackwardEuler(int nx, int nt, double dx, double dt, string filename);
void CrankNicolsonScheme(int nx, int nt, double dx, double dt, string filename);
void JacobiMethod();
void tridiagonalSolver(vec& u, vec b, double diag, double offdiag, int n);

#endif // FUNCTIONS_H
