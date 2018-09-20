#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <time.h>
#include <armadillo>
#include <string>
using namespace std;
using namespace arma;
ofstream ofile;

const double zero = 10e-10;  //Constant which defines the zero point
const double infi = 10e10;   //Same for infinity point
const double pi = 3.141592; //M_pi
// g++ -o test.x Project2.cpp -larmadillo -llapack -lblas
void analytic_eigenvalues(mat A); //Generates analytic eigenvalues using the definition from the exercise text
double max_value_indexes(mat A, int N, int &k, int &l); // Returns indexes for max absolute value in matrix A, as (row, column)
mat generate_A_matrix(int N, vec a, vec d); //Generates the matrix A with diagonal vec d and upper and lower diagonals vec a.
void Jacobi_Rotation_algorithm(mat& A, int N, int k, int l); //Takes as an input the matrix A and S. Outputs B such that B=S^T  A   S


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
  return 0;
}

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
