#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <time.h>
#include <armadillo>
using namespace std;
using namespace arma;
ofstream ofile;

const double zero = 10e-10;  //Constant which defines the zero point
const double infi = 10e10;   //Same for infinity point
const double pi = 3.141592; //M_pi

double analytic_eigenvalues(int N); //Generates analytic eigenvalues using the definition from the exercise text
int max_value_indexes(mat A, int N); //Returns indexes for max absolute value in matrix A, as (row, column)
mat generate_A_matrix(int N, vec a, vec d); //Generates the matrix A with diagonal vec d and upper and lower diagonals vec a.
double t(double tau);
mat Jacobi_Rotation_algorithm(mat A, mat S); //Takes as an input the matrix A and S. Outputs B such that B=S^T  A   S


int main(int argc, char* argv[])
{
  int N=10, iteration=0;
  // Initialization of the program. Generate special case diagonals and initial A matrix.
  vec a = ones<vec>(N-2) * -1; //Generating special case diagonals
  vec d = ones<vec>(N-1) * 2; //Same here
  mat A = generate_A_matrix(N, a, d);
  // This matrix will be updated throughout the algorithm.
  // The generate_A_matrix function can reset it to its original state.

  double maxval, epsilon=10e-8;
  while(maxval>epsilon && iteration<=explode){ //Main algorithm loop. Checks the current (nondiagonal) maxval is sufficiently large for another iteration.
    //Do something

    iteration++
  }


  double h=1/(N+1);
  return 0;
}

double analytic_eigenvalues(int N){
  double h=1/(double(N)+1);
  double a = -1/(h*h);
  double d = 2/(h*h);
  vec lambda_analytic = zeros<vec>(N-1);
  for (int j=0; j<(N-1); j++){
    double ana = d + 2*a*cos(double(j)*pi/(double(N)+1));
    lambda_analytic(j) = ana;
  }
  cout << lambda_analytic << endl;
}

int max_value_indexes(mat A, int N){
  double maxval=0, val;
  int k, l;
  for (int i=0; i<(N-1); i++){      //Loop over all rows of A.
    for (int j=i+1; j<(N-1); i++){  //Loop from column i+1 to save time (symmetry)
      val = A(i, j);
      if (abs(val)>maxval){         //Check the absolute value, as it can have negative indexes
        k=i; l=j;                   //Saving the indexes in values k and l
      }
    }
  }
  return k, l;
}

mat generate_A_matrix(int N, vec a, vec d){
  mat A = zeros<mat>((N-1),(N-1));
  for (int i=0; i<(N-1); i++){ //This loop generates the diagonal
    A(i, i) = d(i);
  }
  for(int i=0; i<(N-2); i++){ //Generate upper and lower diagonals
    A(i,i+1)=-1;
    A(i+1,i)=-1;
  }
  return A;
}

double t(double tau) {
  if (tau > 0) {
    return 1.0/(tau + sqrt(1 + tau*tau));
  } else {
    return -1.0/(tau - sqrt(1 + tau*tau));
  }
}

mat Jacobi_Rotation_algorithm(mat A, mat S){
  mat ST = inplace_trans(S);
  return ST * A * S
}
