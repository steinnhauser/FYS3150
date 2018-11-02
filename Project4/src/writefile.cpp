#include "writefile.h"

void write_data_file(double temp, vector<int> energy_vec,
  vector<int> energy2_vec, vector<int> magnet_vec, vector<int> magnet2_vec,
  vector<int> mc_cycles_vec, vector<int> accepted_vec)
{
  // write E, M, E**2, M**2, timestep Mcs and no. of accepted states
  ofstream ofile;
  ofile.open("datafile.txt");
  ofile << "T= " << temp << endl;
  ofile << setw(20) << "E" << setw(20) << "E^2";
  ofile << setw(20) << "M" << setw(20) << "M^2" << setw(20) << "Mcs";
  ofile << setw(20) << "Acc" << endl;

  int length = energy_vec.size();

  for (int i=0; i<length; i++)
  {
    ofile << setw(20) << setprecision(10) << energy_vec[i];
    ofile << setw(20) << setprecision(10) << energy2_vec[i];
    ofile << setw(20) << setprecision(10) << magnet_vec[i];
    ofile << setw(20) << setprecision(10) << magnet2_vec[i];
    ofile << setw(20) << setprecision(10) << mc_cycles_vec[i];
    ofile << setw(20) << setprecision(10) << accepted_vec[i] << endl;
  }
  ofile.close();
  cout << "File written." << endl;
}


void write_temp_avg_file(int mc_cycles, vector<double> temp_vec,
  vector<double> energy_avg_vec, vector<double> magnet_avg_vec)
{
  // write out the average of the equilibrium states as a function of temp
  ofstream ofile;
  ofile.open("avg_datafile.txt");
  ofile << "MC cycles: " << mc_cycles << endl;
  ofile << setw(20) << "T" << setw(20) << "E" << setw(20) << "M" << endl;

  int length = temp_vec.size();

  for (int i=0; i<length; i++)
  {
    ofile << setw(20) << setprecision(10) << temp_vec[i];
    ofile << setw(20) << setprecision(10) << energy_avg_vec[i];
    ofile << setw(20) << setprecision(10) << magnet_avg_vec[i] << endl;
  }
  ofile.close();
  cout << "File written." << endl;
}
