#include <vector>
using namespace std;

int main(int argc, char* argv[])
{

  return 0;
}

void ThomasAlgorithmGeneralized(string fname, int maxexp){
  clock_t start, finish;
  string filename;
  for(int i=1; i<=maxexp; i++){
    filename=fname;
    int n;
    n=pow(10.0, i);
    filename.append(to_string(i));
    double *d_vec = new double [n+2]; double *dt_vec = new double [n+2]; double *f_vec = new double [n+2];
    double *ft_vec = new double [n+2]; double *a_vec = new double [n+1]; double *c_vec = new double [n+1]; double *u_vec = new double [n+2];

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

    for(int i=n; i>0; i--){
        u_vec[i]=(ft_vec[i]-c_vec[i]*u_vec[i+1])/dt_vec[i];
    }

    finish = clock();
    double clocks = (finish-start);
    double timeElapsed = clocks/CLOCKS_PER_SEC;
    cout << "N=10^" << i << ": " << timeElapsed << "s" << endl;


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

    delete [] d_vec; delete [] dt_vec; delete [] f_vec; delete [] ft_vec;
    delete [] a_vec; delete [] c_vec; delete [] u_vec;
  }
  cout << "Calculation complete." << endl;
}
