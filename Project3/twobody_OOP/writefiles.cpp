#include "writefiles.h"

void write_files(cube positions, vec time_vec, string method)
{
  // assuming matrix with the form positions(dimension, timestep, body)
  int N = time_vec.n_elem;
  // loop over body1 and body2
  for (int j=0; j<2; j++) {
    string filename = "./data/planet";
    ofstream ofile;
    filename.append(method);
    filename.append(to_string(j));
    filename.append(".txt");
    ofile.open(filename, ofstream::out | ofstream::trunc);
    ofile << setw(20) << "x: " << setw(20) << "y: " << setw(20) << "z: ";
    ofile << setw(20) << "t: " << endl;
    // loop over time
    for (int t=0; t<N; t++){
      ofile << setw(20) << setprecision(10) << positions(0, t, j);
      ofile << setw(20) << setprecision(10) << positions(1, t, j);
      ofile << setw(20) << setprecision(10) << positions(2, t, j);
      ofile << setw(20) << setprecision(10) << time_vec(t) << endl;
    }
    cout << "File written: " << filename << endl;
    ofile.close();
  }
}
