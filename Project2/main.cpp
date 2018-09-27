// Compile: g++ -o test.x main.cpp functions.cpp test_functions.cpp -larmadillo -llapack -lblas
#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <armadillo>
#include "test_functions.h"
#include "functions.h"

using namespace std;
using namespace arma;

ofstream ofile;

int main(int argc, char* argv[])
{
  int N=200, iteration=0;
  // Initialization of the program. Generate special case diagonals and initial A matrix.
  //double h=1.0/(N);
  vec a = ones<vec>(N-2); // Generating special case diagonal
  vec d = ones<vec>(N-1); // Generating off the two diagonals above/below main diagonal
  mat R = eye<mat>(N-1,N-1);
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
  double wr = 1;//0.01;
  double rho_max = 10;
  double rho_0 = 0;
  vec rho = zeros<vec>(N-1);
  double h = (rho_max - rho_0)/(N);
  a *= -1.0/(h*h);
  d *= 2.0/(h*h);
  // loop over diagonal elements:
  for (int i=0; i<N-1; i++) {
    rho(i) = rho_0 + (i+1)*h;
    d(i) += wr*wr*rho(i)*rho(i) + 1.0/rho(i);
  }

  mat A = generate_A_matrix(N, a, d);
  mat A_original = generate_A_matrix(N, a, d);//A;
  // This matrix will be updated throughout the algorithm.
  // The generate_A_matrix function can reset it to its original state.
  double maxvalue = 10.;
  double epsilon = 1e-14;
  int explode = 100000;
  int k, l;
  // loop until nondiagonal maxvalue is smaller than epsilon OR max iterations
  while ( maxvalue > epsilon && iteration < explode ) { // Main algorithm loop
    maxvalue = max_value_indexes(A, N, k, l);
    iteration++;
    Jacobi_Rotation_algorithm(A, R, N, k, l);
  }
  cout << "Jacobi's method done, number of iterations: " << iteration << endl;

  double eigval;
  vec eigvec = zeros<vec>(N-1);
  find_lowest_eigval_eigvec_pair(eigval, eigvec, A, A_original, R, N);
  cout << "lowest eigenpair found, with eigenvalue: " << eigval << endl;
  // file writing
  ofile.open("project2.txt", std::ofstream::out | std::ofstream::trunc);
  ofile << setw(10) << "lambda: " << eigval << endl;
  ofile << setw(20) << "rho:" << setw(20) << "eigvec: " << endl;
  for (int i=0; i<N-1; i++) {
    ofile << setw(20) << setprecision(10) << rho(i);
    ofile << setw(20) << setprecision(10) << eigvec(i) << endl;
  }
  ofile.close();
  cout << "file written" << endl;

  test_max_value_indices();
  test_eigenvalues();
  test_orthogonality();
  cout << "test functions passed" << endl;

  return 0;
}
