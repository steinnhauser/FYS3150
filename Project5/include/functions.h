#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <armadillo>
#include <string>
#include <fstream>
#include <iomanip>

using namespace arma;
using namespace std;

void JacobiMethod();
void explicitForwardEuler();
void implicitBackwardEuler();
void CrankNicolsonScheme();
void tridiagonalSolver(mat& u, double d, double e, int n, int t_new);
void writeMatrixFile(string filename, mat u);

#endif // FUNCTIONS_H
