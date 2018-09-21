#include <armadillo>
#include <iostream>
#include <vector>
#include "test_functions.h"
#include "functions.h"

using namespace std;
using namespace arma;

void test_max_value_indices() {
  int N = 10;
  vec a = ones<vec>(N-2) * -1.0;
  vec d = ones<vec>(N-1) * 2.0;
  mat A = generate_A_matrix(N, a, d);
  A(2,4) = -5.0; // indices k = 2, l = 4
  int k,l;
  double maxval;
  maxval = max_value_indexes(A,N,k,l);
  if (maxval != 5.0 || k != 2 || l != 4) {
    cout << "test_max_value_indexes failed!" << endl;
    exit(1);
  }
}

void test_eigenvalues() {
  /* Generating a 3x3 matrix,
  then performing jacobi's algo,
  then sorting the eigenvalues from smallest to largest.
  finally testing the eigenvalues vs. analytic eigenvalues */
  int N = 4; // 3 x 3 matrix
  vec a = ones<vec>(N-2) * -1.0;
  vec d = ones<vec>(N-1) * 2.0;
  mat A = generate_A_matrix(N, a, d); // has analytic eigenvalues
  double maxvalue = 10.;
  double epsilon = 10e-12;
  int explode = 50000;
  int k, l;
  int iteration=0;
  while(maxvalue>epsilon && iteration<=explode){
    maxvalue = max_value_indexes(A, N, k, l);
    iteration++;
    Jacobi_Rotation_algorithm(A, N, k, l);
  }
  vector<double> numerical_eigenvalues;
  for (int i=0; i<3; i++) {
    numerical_eigenvalues.push_back(A(i,i));
  }
  sort(numerical_eigenvalues.begin(), numerical_eigenvalues.end());
  //compare with d + 2a cos...
}

void test_orthogonality() {
  // test two random column vectors and that orthogonality is preserved
}
