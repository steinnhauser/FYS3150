// Compile: g++ -o test.x main.cpp functions.cpp test_functions.cpp -larmadillo -llapack -lblas
#include <iostream>
#include <cmath>
#include <fstream>
//#include <iomanip>
#include <armadillo>
#include "test_functions.h"
#include "functions.h"

using namespace std;
using namespace arma;

int main(int argc, char* argv[])
{
  int N=200, iteration=0;
  // Initialization of the program. Generate special case diagonals and initial A matrix.
  //double h=1.0/(N);
  vec a = ones<vec>(N-2); // Generating special case diagonal
  vec d = ones<vec>(N-1); // Generating off the two diagonals above/below main diagonal

  // QUANTUM EXTENSION
  double rho_0 = 0;
  double rho_max = 10;
  double h = (rho_max - rho_0)/N;
  a *= -1.0/(h*h);
  d *= 2.0/(h*h);
  double rho_i;
  for (int i=0; i<N-1; i++) {
    rho_i = rho_0 + (i+1)*h;
    d(i) += rho_i*rho_i;
  }
  mat A = generate_A_matrix(N, a, d);
  // This matrix will be updated throughout the algorithm.
  // The generate_A_matrix function can reset it to its original state.

  double maxvalue = 10.;
  double epsilon = 1e-12;
  int explode = 50000;
  int k, l;
  while(maxvalue>epsilon && iteration<=explode){ //Main algorithm loop. Checks the current (nondiagonal) maxval is sufficiently large for another iteration.
    //Do something
    maxvalue = max_value_indexes(A, N, k, l);
    iteration++;
    Jacobi_Rotation_algorithm(A, N, k, l);
  }
  //A.print("matrix A:" );
  cout << endl;
  vec eigvals = zeros<vec>(N-1);
  for(int i=0; i<N-1; i++){
    eigvals(i) = A(i,i);
  }
  sort(eigvals.begin(), eigvals.end());

  cout << "eigenvalues:" << endl;
  for (int i=0; i<5; i++) {
    cout << eigvals(i) << ", ";
  }
  cout << endl;
  //cout << "number of iterations: " << iteration << endl;
  test_max_value_indices();
  test_eigenvalues();
  test_orthogonality();
  return 0;
}
