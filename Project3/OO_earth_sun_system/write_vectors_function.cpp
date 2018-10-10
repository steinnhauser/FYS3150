#include <iomanip>
#include <iostream>
#include <armadillo>
#include "write_vectors_function.h"
#include <string>

using namespace std;
using namespace arma;

void write_vectors(vec x, vec y, vec z, vec kin_energy, vec pot_energy, vec t, string fn, string title)
{
  if(x.n_elem!=y.n_elem || x.n_elem!=z.n_elem || x.n_elem!=t.n_elem){
    cout << "Value error: Vectors do not have the same lengths." << endl;
    exit(1);
  }
  else{
    //string filename = "./data/project2_";
    //filename.append(to_string(j) + ".txt");
    string FN = "./data/";
    FN.append(fn + ".txt");
    ofstream ofile;
    ofile.open(FN, std::ofstream::out | std::ofstream::trunc);

    ofile << title << endl;
    ofile << setw(20) << "x: " << setw(20) << "y: " << setw(20) << "z: ";
    ofile << setw(20) << "Ek:" << setw(20) << "Ep:" << setw(20) << "t: " << endl;

    double factor = 100.0;
    int Length = x.n_elem/factor;
    for (int i=0; i<Length; i*=factor) {
      ofile << setw(20) << setprecision(10) << x(i);
      ofile << setw(20) << setprecision(10) << y(i);
      ofile << setw(20) << setprecision(10) << z(i);
      ofile << setw(20) << setprecision(10) << kin_energy(i);
      ofile << setw(20) << setprecision(10) << pot_energy(i);
      ofile << setw(20) << setprecision(10) << t(i) << endl;
    }
    ofile.close();
    cout << "File " << FN << " written." << endl;
  }
}
