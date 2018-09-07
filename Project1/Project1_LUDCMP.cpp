#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <armadillo>
using namespace std;
ofstream ofile;
//First, build vectors d and b.
//Segmentation fault... sjekk indexer
//Hvis ikke, skriv .at(index)

void ludcmp(double **a, int n, int *indx, double *d);
void lubksb(double **a, int n, int *indx, double *b);

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






void ludcmp(double **a, int n, int *indx, double *d){
   int      i, imax, j, k;
   double   big, dum, sum, temp, *vv;

  vv = new(nothrow) double [n];
  if(!vv) {
    printf("\n\nError in function ludcm():");
    printf("\nNot enough memory for vv[%d]\n",n);
    exit(1);
  }

   *d = 1.0;                              // no row interchange yet
   for(i = 0; i < n; i++) {     // loop over rows to get scaling information
      big = ZERO;
      for(j = 0; j < n; j++) {
         if((temp = fabs(a[i][j])) > big) big = temp;
      }
      if(big == ZERO) {
         printf("\n\nSingular matrix in routine ludcmp()\n");
         exit(1);
      }
      vv[i] = 1.0/big;                 // save scaling */
   } // end i-loop */

   for(j = 0; j < n; j++) {     // loop over columns of Crout's method
      for(i = 0; i< j; i++) {   // not i = j
         sum = a[i][j];
     for(k = 0; k < i; k++) sum -= a[i][k]*a[k][j];
     a[i][j] = sum;
      }
      big = ZERO;   // initialization for search for largest pivot element
      for(i = j; i< n; i++) {
         sum = a[i][j];
     for(k = 0; k < j; k++) sum -= a[i][k]*a[k][j];
     a[i][j] = sum;
     if((dum = vv[i]*fabs(sum)) >= big) {
        big = dum;
        imax = i;
     }
      } // end i-loop
      if(j != imax) {    // do we need to interchange rows ?
         for(k = 0;k< n; k++) {       // yes
        dum        = a[imax][k];
        a[imax][k] = a[j][k];
        a[j][k]    = dum;
     }
     (*d)    *= -1;            // and change the parit of d
     vv[imax] = vv[j];         // also interchange scaling factor
      }
      indx[j] = imax;
      if(fabs(a[j][j]) < ZERO)  a[j][j] = ZERO;

        /*
        ** if the pivot element is zero the matrix is singular
        ** (at least to the precision of the algorithm). For
        ** some application of singular matrices, it is desirable
        ** to substitute ZERO for zero,
        */

      if(j < (n - 1)) {                   // divide by pivot element
         dum = 1.0/a[j][j];
     for(i=j+1;i < n; i++) a[i][j] *= dum;
      }
   } // end j-loop over columns

   delete [] vv;   // release local memory
} // End: function ludcmp()

void lubksb(double **a, int n, int *indx, double *b){
   int        i, ii = -1, ip, j;
   double     sum;

   for(i = 0; i< n; i++) {
      ip    = indx[i];
      sum   = b[ip];
      b[ip] = b[i];
      if(ii > -1)   for(j = ii; j < i; j++) sum -= a[i][j] * b[j];
      else if(sum) ii = i;
      b[i] = sum;
   }
   for(i = n - 1; i >= 0; i--) {
      sum = b[i];
      for(j = i+1; j < n; j++) sum -= a[i][j] * b[j];
      b[i] = sum/a[i][i];
   }
} // End: function lubksb()
