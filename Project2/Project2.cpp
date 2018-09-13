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

double analytic_eigenvalues(int N);
double max_value_indexes(mat A, int N);
double t(double tau);

int main(int argc, char* argv[])
{
  int N=1000;
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


double max_value_indexes(mat A, int N){
  return k, l
}

double t(double tau) {
  if (tau > 0) {
    return 1.0/(tau + sqrt(1 + tau*tau));
  } else {
    return -1.0/(tau - sqrt(1 + tau*tau));
  }
}
