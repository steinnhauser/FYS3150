#include "writefile.h"

void write_data_file(vec data_vector)
{
  // write E, M, E**2, M**2, temp, mcs?
  ofstream ofile;
  ofile.open("datafile.txt");
  ofile << "" << endl;
  ofile << setw(20) << "E" << setw(20) << "M" << setw(20) << "E^2";
  ofile << setw(20) << "M^2" << setw(20) << "T" << setw(20) << "Mcs" << endl;

  int length = data_vector.n_elem;

  
  ofile << setw(20) << setprecision(10) << data_vector(0);
  ofile << setw(20) << setprecision(10) << data_vector(1);
  ofile << setw(20) << setprecision(10) << data_vector(2);
  ofile << setw(20) << setprecision(10) << data_vector(3);
  ofile << setw(20) << setprecision(10) << data_vector(4);
  ofile << setw(20) << setprecision(10) << data_vector(5);

  ofile.close();
  cout << "File written." << endl;
}
