#ifndef WRITEFILE_H
#define WRITEFILE_H
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

void write_data_file(vector<double> temp_vec, vector<int> energy_vec,
  vector<int> energy2_vec, vector<int> magnet_vec, vector<int> magnet2_vec,
  vector<int> mc_cycles_vec, vector<int> accepted_vec);

#endif // WRITEFILE_H
