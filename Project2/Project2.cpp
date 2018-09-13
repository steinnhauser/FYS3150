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

double Analytic_Eigenvalues(int N);
double maxval();

int main(int argc, char* argv[])
{
  cout << "Hello, World!" << endl;
  int N=1000;
  //i am master
  Analytic_Eigenvalues(N);
  double h=1/(N+1);

  return 0;
}


double Analytic_Eigenvalues(int N){
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
