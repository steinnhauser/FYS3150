#include <iostream>
#include <cmath>
#include <vector>
#include "metropolis.h"
#include "spin_initializer.h"
#include "writefile.h"
//#include "mpi.h"

using namespace std;

int main(int argc, char* argv[]) {
  int L = 20;
  int **spin_matrix = new int* [L];
  for (int spin=0; spin<L; spin++) spin_matrix[spin] = new int[L];
  // initialize spin_matrix: name, length and order: true=ordered, false=random
  int magnetization=0, energy=0;
  Initialize_spins(spin_matrix, L, true, magnetization, energy);
  double Tmin = 1.0;
  double Tmax = 2.4;
  int MC_steps = 200;
  double T_step = 0.05;
  double w[17]; // Boltzmann factors of energy levels -8J to 8J

  vector<double> energy_avg_vec;
  vector<double> magnet_avg_vec;
  vector<double> temp_vec;
  vector<int> energy_vec;
  vector<int> energy2_vec;
  vector<int> magnet_vec;
  vector<int> magnet2_vec;
  vector<int> mc_cycles_vec;
  vector<int> accepted_vec;
  // body and soul of the program
  for (double temp=Tmin; temp<=Tmax; temp+=T_step) {
    // initialize w, dependent of temperature
    temp_vec.push_back(temp);
    double beta = 1./temp;
    for (int i=0; i<17; i++) {
      if (i%4==0) {
        w[i] = exp(-beta*(i-8));
        cout << w[i] << endl;
      } else w[i] = 0;
    }
    // MC cycles
    int acceptedConfigs = 0;
    for (int mc=0; mc<MC_steps; mc++) {
      energy_vec.push_back(energy);
      energy2_vec.push_back(energy*energy);
      magnet_vec.push_back(fabs(magnetization));
      magnet2_vec.push_back(magnetization*magnetization);
      mc_cycles_vec.push_back(mc);
      accepted_vec.push_back(acceptedConfigs);
      acceptedConfigs = 0;
      metropolis(spin_matrix,L,energy,magnetization,acceptedConfigs,w);
    }
    write_data_file(temp, energy_vec,energy2_vec, magnet_vec, magnet2_vec,
                    mc_cycles_vec, accepted_vec);
    // calculate the average of last 50 % of the data
    double E_avg=0, M_avg=0;
    int length = temp_vec.size();
    for (int i=length/2; i<length; i++)
    {
      E_avg += energy_vec[i];
      M_avg += magnet_vec[i];
    }
    E_avg/=length; M_avg/=length;
    // save all the average energies and magnetizations as a function of temp
    energy_avg_vec.push_back(E_avg);
    magnet_avg_vec.push_back(M_avg);
  }
  write_temp_avg_file(MC_steps, temp_vec, energy_avg_vec, magnet_avg_vec);

  for (int x=0; x<L; x++) {
    for (int y=0; y<L; y++) {
      cout << spin_matrix[x][y] << " ";
    }
    cout << endl;
  }

  for(int i=0; i<L; ++i) delete[] spin_matrix[i];
  delete[] spin_matrix;

  // MPI_Init (&argc, &argv);
  // MPI_Comm_size (MPI_COMM_WORLD, &numprocs);
  // MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);
  // MPI_Finalize ();
  // Run: mpirun -n 2 ./hw.x
  return 0;
}
