#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;
ofstream ofile;
//First, build vectors d and b.
//Segmentation fault... sjekk indexer
//Hvis ikke, skriv .at(index)
int main(int argc, char* argv[])
{
    //Variable n.
    //Initialize matrix vectors, saving ram space.
    //double d_vec[n+1], dt_vec[n+1], f_vec[n+1], ft_vec[n+1], a_vec[n+1], c_vec[n+1], u_vec[n+1];

    string fname;
    int maxexp;
    maxexp = atoi(argv[2]);

    for(int i=1; i<=maxexp; i++){
      fname=argv[1];

      int n;
      n=pow(10.0, i);
      fname.append(to_string(n));
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
      //write file with current i and n:
      fname.append(".txt");
      ofile.open(fname);
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
      delete [] d_vec; delete [] dt_vec; delete [] f_vec; delete [] ft_vec;
      delete [] a_vec; delete [] c_vec; delete [] u_vec;
    }
    cout << "Calculation complete." << endl;
    return 0;
}
