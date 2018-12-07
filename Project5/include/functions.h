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
void explicitForwardEuler(int nx, int nt, double dx, double dt, string filename);
void implicitBackwardEuler(int nx, int nt, double dx, double dt, string filename);
void CrankNicolsonScheme(int nx, int nt, double dx, double dt, string filename);
void JacobiMethod();
void tridiagonalSolver(mat& u, double d, double e, int n, int t_new);

#endif // FUNCTIONS_H
