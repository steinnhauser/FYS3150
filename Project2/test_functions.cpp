#define CATCH_CONFIG_MAIN
#include <armadillo>
#include "catch.hpp"
#include "test_functions.h"
#include "functions.h"

using namespace arma;

void test_max_value_indexes() {
  int N = 10;
  vec a = ones<vec>(N-2) * -1.0; // Generating special case diagonal
  vec d = ones<vec>(N-1) * 2.0;
  mat A = generate_A_matrix(N, a, d);
  A(2,4) = -5.0 // indices k = 2, l = 4
  int k,l;
  maxval = max_value_indexes(A,N,k,l);
  REQUIRE( maxval == 5.0 );
  REQUIRE( k == 2 );
  REQUIRE( l == 4 );
}

void test_eigenvalues() {
  // generate some matrix where eigenvalues are known


}

void test_orthogonality() {
  // test two random column vectors and that orthogonality is preserved


}
