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
  int N=10, iteration=0;
  // Initialization of the program. Generate special case diagonals and initial A matrix.
  double h=1.0/(N);
  vec a = ones<vec>(N-2) * -1.0/(h*h); // Generating special case diagonal
  vec d = ones<vec>(N-1) * 2.0/(h*h); // Generating off the two diagonals above/below main diagonal
  mat A = generate_A_matrix(N, a, d);
  // This matrix will be updated throughout the algorithm.
  // The generate_A_matrix function can reset it to its original state.

  double maxvalue = 10.;
  double epsilon = 10e-12;
  int explode = 50000;
  int k, l;
  while(maxvalue>epsilon && iteration<=explode){ //Main algorithm loop. Checks the current (nondiagonal) maxval is sufficiently large for another iteration.
    //Do something
    maxvalue = max_value_indexes(A, N, k, l);
    iteration++;
    Jacobi_Rotation_algorithm(A, N, k, l);
  }
  A.print();
  cout << endl;
  for(int i=0; i<N-1; i++){
    cout << A(i,i) << ", ";
  }
  cout << "number of iterations: " << iteration << endl;
  test_max_value_indices();
  test_eigenvalues();
  return 0;
}
