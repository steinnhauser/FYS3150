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
const double pi = 3.141592;

double analytic_eigenvalues(int N); //Generates analytic eigenvalues using the definition from the exercise text
int max_value_indexes(mat A, int N); //Returns indexes for max absolute value in matrix A, as (row, column)
double generate_A_matrix(int N, vec a, vec d); //Generates the matrix A with diagonal vec d and upper and lower diagonals vec a.
double t(double tau);


int main(int argc, char* argv[])
{
  int N=1000;
  generate_A_matrix(int N, vec a, vec d);
  analytic_eigenvalues(N);
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
  double maxval=0;
  int k, l;
  for (int i=0; i<(N-1); i++){      //Loop over all rows of A.
    for (int j=i+1; j<(N-1); i++){  //Loop from column i+1 to save time (symmetry)
      val = A(i, j)
      if (abs(val)>maxval){         //Check the absolute value, as it can have negative indexes
        k=i; l=j;                   //Saving the indexes in values k and l
      }
    }
  }
  return k, l
}

double generate_A_matrix(int N, vec a, vec d){
  mat A = zeros<mat>((N-1),(N-1));
  for (int i=0; i<(N-1); i++){ //This loop generates the diagonal
    for (int j=0; j<(N-1); j++){
      A(i, j) = d(i)
    }
  }

  for (int i=0; i<(N-2); i++){ // This loop generates the upper and lower diagonals
    for (int j=0; j<(N-2); j++){
      A(i+1, j) = a(i)
      A(i, j+1) = a(i)
    }
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
