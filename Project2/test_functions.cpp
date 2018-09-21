#include <armadillo>
#include <iostream>
#include "test_functions.h"
#include "functions.h"

using namespace std;
using namespace arma;

void test_max_value_indexes() {
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
  int N = 4; // yields 3x3 matrix
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
  double eigval1, eigval2, eigval3;
  eigval1 = A(0,0);
  eigval2 = A(1,1);
  eigval3 = A(2,2);
  cout << eigval1 << " " << eigval2 << " " << eigval3 << " " << endl; //compare with d + 2a cos...
}

void test_orthogonality() {
  // test two random column vectors and that orthogonality is preserved
}
