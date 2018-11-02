#ifndef WRITEFILE_H
#define WRITEFILE_H
#include <iomanip>
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

void write_data_file(double temp, vector<int> energy_vec,
  vector<int> energy2_vec, vector<int> magnet_vec, vector<int> magnet2_vec,
  vector<int> mc_cycles_vec, vector<int> accepted_vec);

void write_temp_avg_file(int mc_cycles, vector<double> temp_vec,
  vector<double> energy_avg_vec, vector<double> magnet_avg_vec);

#endif // WRITEFILE_H
