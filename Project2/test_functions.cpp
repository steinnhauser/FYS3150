#include "test_functions.h"
#include <cmath>
#include <armadillo>
using namespace std;
using namespace arma;

void analytic_eigenvalues(mat A){
  vec eigval;
  mat eigvec;
  eig_sym(eigval, eigvec, A);
  eigval.print();
}

double max_value_indexes(mat A, int N, int& k, int& l){
  double maxval=0, val;
  for (int i=0; i<(N-1); i++){      //Loop over all rows of A.
    for (int j=i+1; j<(N-1); j++){  //Loop from column i+1 to save time (symmetry)
      val = A(i, j);
      if (fabs(val)>maxval){         //Check the absolute value, as it can have negative indexes
        k=i; l=j;                   //Saving the indexes in values k and l
        maxval = fabs(val);
      }
    }
  }
  return maxval;
}

mat generate_A_matrix(int N, vec a, vec d){
  mat A = zeros<mat>(N-1,N-1);
  A(0,0) = d(0); A(0,1) = a(0); // first row
  for (int i=1; i<N-2; i++) { // All inner rows in tridiag matrix filled row by row
    A(i, i) = d(i);
    A(i,i+1) = a(i);
    A(i,i-1) = a(i);
  }
  A(N-2,N-2) = d(N-2); A(N-2,N-3) = a(N-3); // last row
  return A;
}

void Jacobi_Rotation_algorithm(mat& A, int N, int k, int l){
  // Obtaining values tau, t, c, s
  double tau, t, s, c, a_ik, a_il, a_kk, a_ll;
  tau = (A(l,l) - A(k,k))/(2*A(k,l));
  if (tau >= 0) {
    t = 1.0/(tau + sqrt(1 + tau*tau));
  } else {
    t = -1.0/(-tau + sqrt(1 + tau*tau));
  }
  c = 1/(sqrt(1 + t*t));
  s = c*t;
  double cc = c*c;
  double ss = s*s;
  double cs = c*s;
  double cc_ss = cc - ss;

  a_kk = A(k,k)*cc - 2*A(k,l)*cs + A(l,l)*ss;
  a_ll = A(l,l)*cc + 2*A(k,l)*cs + A(k,k)*ss;
  A(k,l) = 0; //(A(k,k) - A(l,l))*cs + A(k,l)*cc_ss;
  //cout << A(k,l) << " ";
  A(l,k) = A(k,l);
  A(k,k) = a_kk;
  A(l,l) = a_ll;

  for (int i=0; i<N-1; i++) {
    if (i != k && i != l) {
      a_ik = A(i,k)*c - A(i,l)*s;
      a_il = A(i,l)*c + A(i,k)*s;

      A(i,k) = a_ik;
      A(i,l) = a_il;


      A(k,i) = a_ik;
      A(l,i) = a_il;
    }
  }
}
