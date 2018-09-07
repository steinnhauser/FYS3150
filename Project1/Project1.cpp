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

void ThomasAlgorithm(string fname, int maxexp);
void LUDecompFunc(string fname, int maxexp);

//First, build vectors d and b.
//Segmentation fault... sjekk indexer
//Hvis ikke, skriv .at(index)
int main(int argc, char* argv[])
{
    string fname;
    int maxexp;
    fname=argv[1];
    maxexp = atoi(argv[2]);

    //ThomasAlgorithm(fname, maxexp);
    LUDecompFunc(fname, maxexp);

    //Variable n.
    //Initialize matrix vectors, saving ram space.
    //double d_vec[n+1], dt_vec[n+1], f_vec[n+1], ft_vec[n+1], a_vec[n+1], c_vec[n+1], u_vec[n+1];
}


void ThomasAlgorithm(string fname, int maxexp){
  //string fname;
  //int maxexp;
  //maxexp = atoi(argv[2]);
  clock_t start, finish;
  string filename;

  for(int i=1; i<=maxexp; i++){
    filename=fname;

    int n;
    n=pow(10.0, i);
    filename.append(to_string(i));
    double *d_vec = new double [n+2]; double *dt_vec = new double [n+2]; double *f_vec = new double [n+2];
    double *ft_vec = new double [n+2]; double *a_vec = new double [n+1]; double *c_vec = new double [n+1]; double *u_vec = new double [n+2];

    //double d_vec[n+2]; double dt_vec[n+2]; double f_vec[n+2]; double ft_vec[n+2]; double a_vec[n+1]; double c_vec[n+1]; double u_vec[n+2];

    double x0=0, h, x;
    h=1/(double(n+1));

    //Fill f array analytically:
    for (int i=0; i<=n+1; i++){
        x=x0+h*double(i);
        f_vec[i]=h*h*100*exp(-10*x);
    }
    //Special case diagonals
    for(int i=1; i<=n; i++){
        d_vec[i]=2;
        a_vec[i]=-1;
        c_vec[i]=-1;
        //dt_vec[i]=0;
        //ft_vec[i]=0;
        //u_vec[i]=0;       //Initial values of u: u(0)=u(1)=0
    }

    dt_vec[1]=d_vec[1];
    ft_vec[1]=f_vec[1];
    u_vec[0]=0;
    u_vec[n+1]=0;


    start = clock();

    //First for-loop to create b vector.
    for(int i=2; i<=n; i++){
        dt_vec[i]=d_vec[i] - c_vec[i-1]*a_vec[i-1]/dt_vec[i-1];
        ft_vec[i]=f_vec[i] - ft_vec[i-1]*a_vec[i-1]/dt_vec[i-1];
    }
    u_vec[n]=ft_vec[n]/dt_vec[n];

    //Compute u=f/d:j
    for(int i=n; i>0; i--){
        u_vec[i]=(ft_vec[i]-c_vec[i]*u_vec[i+1])/dt_vec[i];
    }

    finish = clock();
    double clocks = (finish-start);
    double timeElapsed = clocks/CLOCKS_PER_SEC;

    cout << "N=10^" << i << ": " << timeElapsed << "s" << endl;

    /*
    //write file with current i and n:
    filename.append(".txt");
    ofile.open(filename);
    //ofile << setiosflags(ios::showpoint | ios::uppercase);
    for(double i=1; i<=n; i++){
        double h;
        h=1/(double(n)+1);
        ofile << setprecision(10) << setw(20) << h*i;
        ofile << setprecision(10) << setw(20) << 1-(1-exp(-10))*h*i - exp(-10*h*i);
        ofile << setprecision(10) << setw(20) << u_vec[int(i)];
        ofile << setprecision(10) << setw(20) << log10(fabs((- (1-(1-exp(-10))*h*i - exp(-10*h*i)) + u_vec[int(i)])/(1-(1-exp(-10))*h*i - exp(-10*h*i)))) << endl;
    }
    ofile.close();
    */
    delete [] d_vec; delete [] dt_vec; delete [] f_vec; delete [] ft_vec;
    delete [] a_vec; delete [] c_vec; delete [] u_vec;
  }
  cout << "Calculation complete." << endl;
}

void LUDecompFunc(string fname, int maxexp){
  clock_t start, finish;
  string filename;
  for (float i=0.5; i<=maxexp; i++){
    filename = fname;
    filename.append(to_string(i));
    int n=pow(10.0,i);
    double h;
    h=1./(n+1);
    mat A = zeros<mat>(n,n);

    for(int i=0; i<n; i++){
      A(i,i)=2;
    }
    for(int i=0; i<(n-1); i++){
      A(i,i+1)=-1;
      A(i+1,i)=-1;
    }

    vec b = zeros<vec>(n);
    for(int i=0; i<n; i++){
      b(i)=100*exp(-10*i*h)*h*h;
    }

    start = clock();

    mat L, U;
    vec x, z, u;
    lu(L,U,A);

    z = solve(L, b);
    u = solve(U, z);


    finish = clock();
    double clocks = (finish-start);
    double timeElapsed = clocks/CLOCKS_PER_SEC;

    cout << "N=10^" << i << ": " << timeElapsed << "s" << endl;


    /*
    filename.append(".txt");
    ofile.open(filename);
    //ofile << setiosflags(ios::showpoint | ios::uppercase);
    for(double i=1; i<n; i++){
        double h;
        h=1/(double(n)+1);
        ofile << setprecision(10) << setw(20) << h*i;
        ofile << setprecision(10) << setw(20) << 1-(1-exp(-10))*h*i - exp(-10*h*i);
        ofile << setprecision(10) << setw(20) << u(int(i));
        ofile << setprecision(10) << setw(20) << log10(fabs((- (1-(1-exp(-10))*h*i - exp(-10*h*i)) + u(int(i)))/(1-(1-exp(-10))*h*i - exp(-10*h*i)))) << endl;
    }
    ofile.close();
    */
  }


  //AX=B
  //X = solve(A,B)
}
