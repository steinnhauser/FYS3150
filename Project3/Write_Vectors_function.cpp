#include<iomanip>
#include<iostream>
#include<armadillo>
#include"Write_Vectors_function.h"
#include<string>

using namespace std;
using namespace arma;

void Write_Vectors(vec x, vec y, vec z, vec t, string fn, string title)
{
  if(x.n_elem!=y.n_elem || x.n_elem!=z.n_elem || x.n_elem!=t.n_elem){
    cout << "Value error: Vectors do not have the same lengths." << endl;
    exit(1);
  }
  else{
    //string filename = "./data/project2_";
    //filename.append(to_string(j) + ".txt");
    ofstream ofile;
    ofile.open(fn, std::ofstream::out | std::ofstream::trunc);

    ofile << title << endl;
    ofile << setw(20) << "x: " << setw(20) << "y: " << setw(20) << "z: " << setw(20) << "t: " << endl;

    int Length = x.n_elem;
    for (int i=0; i<Length; i++) {
      ofile << setw(20) << setprecision(10) << x(i);
      ofile << setw(20) << setprecision(10) << y(i);
      ofile << setw(20) << setprecision(10) << z(i);
      ofile << setw(20) << setprecision(10) << t(i) << endl;
    }
    ofile.close();
  }
}
