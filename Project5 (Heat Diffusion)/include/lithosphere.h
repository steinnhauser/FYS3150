#ifndef LITHOSPHERE_H
#define LITHOSPHERE_H
#include <armadillo>
#include <string>
#include <fstream>
#include <iomanip>
#include <math.h>

using namespace arma;
using namespace std;

void JacobiMethodLithosphere(int situation, string filename);
void boundaryNoHeat(mat& u, int nx, int ny);
void boundaryNaturalHeat(mat& u, int nx, int ny);
void reachNaturalHeatEquilibrium(mat& u, int maxiter, double tol, double factor1,
   double factor2, vec Qvec, int nx, int ny, int nt, double scale);
double periodicDelta(mat u_guess, int i, int j, int nx, int ny);

#endif // LITHOSPHERE_H
