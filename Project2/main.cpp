// Compile: g++ -o test.x main.cpp functions.cpp test_functions.cpp -larmadillo -llapack -lblas
#include <iostream>
#include <cmath>
#include <armadillo>
#include "test_functions.h"
#include "functions.h"

using namespace std;
using namespace arma;

int main(int argc, char* argv[])
{
  // test functions:
  test_max_value_indices();
  test_eigenvalues();
  test_orthogonality();
  cout << "test functions passed." << endl;
  // Initialization of the program. Generate special case diagonals and initial A matrix.
  //double h=1.0/(N);
  // QUANTUM EXTENSION: with one electron. initial matrix
  /*
  double rho_0 = 0;
  double rho_max = 10;
  double h = (rho_max - rho_0)/(N);
  a *= -1.0/(h*h);
  d *= 2.0/(h*h);
  double rho_i;
  for (int i=0; i<N-1; i++) {
    rho_i = rho_0 + (i+1)*h;
    d(i) += rho_i*rho_i;
  }
  */
  // QUANTUM EXTENSION: with two electrons. initial matrix
  vec wrvec = zeros<vec>(4);
  wrvec(0) = 0.01;
  wrvec(1) = 0.5;
  wrvec(2) = 1.0;
  wrvec(3) = 5.0;

  // loop over different omega_r = wr
  for (int j=0; j<4; j++) {
    int N=200;
    double wr = wrvec(j);
    double rho_max = 5;
    double rho_0 = 0;
    double h = (rho_max - rho_0)/(N);
    vec a = ones<vec>(N-2); // upper and lower diagonals
    vec d = ones<vec>(N-1); // main diagonal
    a *= -1.0/(h*h);
    d *= 2.0/(h*h);

    // adding of the extra term V (potential) to the main diagonal d
    vec rho = zeros<vec>(N-1);
    for (int i=0; i<N-1; i++) { // loop over diagonal elements:
      rho(i) = rho_0 + (i+1)*h;
      d(i) += wr*wr*rho(i)*rho(i) + 1.0/rho(i); // potential term
    }

    // Jacobi's method:
    mat R = eye<mat>(N-1,N-1); // matrix where columns will store eigenvectors
    mat A = generate_A_matrix(N, a, d); // this will be changed
    mat A_original = generate_A_matrix(N, a, d); // this will remain unchanged
    double maxvalue = 10.;
    double epsilon = 1e-10;
    int iteration = 0;
    int maxIterations = 100000;
    int k, l;
    // loop until nondiagonal maxvalue is smaller than epsilon OR max iterations
    while ( maxvalue > epsilon && iteration < maxIterations ) { // Main algorithm loop that performs rmatrix otations
      maxvalue = max_value_indexes(A, N, k, l);
      iteration++;
      Jacobi_Rotation_algorithm(A, R, N, k, l);
    }
    cout << "Jacobi's method done, number of iterations: " << iteration << endl;

    // finding the ground state eigenpair:
    double eigval;
    vec eigvec = zeros<vec>(N-1);
    find_lowest_eigval_eigvec_pair(eigval, eigvec, A, A_original, R, N);
    cout << "lowest eigenpair found, with eigenvalue: " << eigval << endl;

    // file writing
    write_file(N, j, eigval, wr, rho, eigvec);
    cout << "file written." << endl;
    cout << "wr = " << wr << " is done." << endl;
  }

  cout << "Done." << endl;
  return 0;
}
