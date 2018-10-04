#include<iomanip>
#include<iostream>
#include<armadillo>
#include"Write_Vectors_function.h"
#include<string>

using namespace std;
using namespace arma;

void Write_Vectors(vec x, vec y, vec z, string fn, string title)
{
  if(size(x)!=size(y) || size(x)!=size(z)){
    cout << "Value error: Vectors do not have the same lengths.";
    exit(1);
  }
  else{
    //string filename = "./data/project2_";
    //filename.append(to_string(j) + ".txt");
    ofstream ofile;
    ofile.open(fn, std::ofstream::out | std::ofstream::trunc);

    ofile << title << endl;
    ofile << setw(10) << "x: " << "y: " << "z: " << endl;

    int Length = size(x);
    for (int i=0; i<Length; i++) {
      ofile << setw(20) << setprecision(10) << x(i);
      ofile << setw(20) << setprecision(10) << y(i);
      ofile << setw(20) << setprecision(10) << z(i) << endl;
    }
    ofile.close();
  }
}
