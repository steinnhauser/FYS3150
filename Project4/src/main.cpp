#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <fstream>
#include <string>
#include "metropolis.h"
#include "spin_initializer.h"
#include "writefile.h"
#include "test_functions.h"
//#include "mpi.h"

using namespace std;

void lattice_solve(int L, int MC_steps, double temp); // finds <E>, <M>, Cv, chi vs. T
void equilibrium_time(int L, int MC_steps); // finds E(mc), M(mc)
void accepted_configs(int L, int MC_steps); // finds avg. accepted configs vs temperature

vector<int> prob_distribution(vector<int> energy_vec); //4d, find P(E) by counting #apperance of E's, L=20, T=1 and T=2.4, compare with sigma_E

// Steinn: maybe use lattice_solve as general function, and do phase transitions in main?
// Simen: Not sure what you want lattice_solve to do. But phase transitions should definitely be parallelized (MPI) in main.

void phase_transition(); //4e, 4 Plots: <E>, <M>, Cv, chi vs. T and for L=20,40,80,100

int main(int argc, char* argv[]) {
  int MC_steps = 20000;
  test_initial_lattice();
  equilibrium_time(20, MC_steps);
  accepted_configs(20, MC_steps);
  /*
  vector<double> energy_avg_vec;
  vector<double> magnet_avg_vec;
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
  */

  // MPI_Init (&argc, &argv);
  // MPI_Comm_size (MPI_COMM_WORLD, &numprocs);
  // MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);
  // MPI_Finalize ();
  // Run: mpirun -n 2 ./hw.x
  return 0;
}

void lattice_solve(int L, int MC_steps, double temp) {
  /*
  Calculate expectation values for Energy and Magnetism, Heat capacity
  and magnetic susceptibility for an LxL lattice for a given number of
  Monte Carlo cycles and temperature
  */
  // initialization
  int **spin_matrix = new int* [L];
  for (int spin=0; spin<L; spin++) spin_matrix[spin] = new int[L];
  int magnetization=0, energy=0;
  Initialize_spins(spin_matrix, L, true, magnetization, energy);
  double beta = 1./temp;
  double w[17];
  for (int i=0; i<17; i++) {
    if (i%4==0) {
      w[i] = exp(-beta*(i-8));
    } else w[i] = 0;
  }
  vector<int> energy_vec;
  vector<int> energy2_vec;
  vector<int> magnet_vec;
  vector<int> magnet2_vec;
  int acceptedConfigs=0;
  // Monte Carlo cycles
  for (int mc=0; mc<MC_steps; mc++) {
    energy_vec.push_back(energy);
    energy2_vec.push_back(energy*energy);
    magnet_vec.push_back(magnetization);
    magnet2_vec.push_back(magnetization*magnetization);
    acceptedConfigs = 0;
    metropolis(spin_matrix,L,energy,magnetization,acceptedConfigs,w);
  }

  // calculate the mean values of E, M, E^2 and M^2, C_V and chi
  // write file

  for(int i=0; i<L; ++i) delete[] spin_matrix[i]; delete[] spin_matrix;
}

void equilibrium_time(int L, int MC_steps) {
  /*
  Analyze the evolution of a 20x20 lattice for two temperatures
  T=1.0 and T=2.4 and two initial states ordered/random.
  Write files with: MC-cycles, Energy and Magnetization.
  */
  int **spin_matrix = new int* [L];
  for (int spin=0; spin<L; spin++) spin_matrix[spin] = new int[L];
  // loop over ordered and random initial state
  for (int order=0; order<2; order++) {
    // loop over two temperatures T=1.0 and T=2.4
    for (double temp = 1.0; temp<=2.4; temp+=1.4) {
      // initialization
      int magnetization=0;
      int energy=0;
      int acceptedConfigs=0;
      vector<int> energy_vec;
      vector<int> magnet_vec;
      vector<int> mc_cycles_vec;
      double beta = 1./temp;
      double w[17];
      for (int i=0; i<17; i++) {
        if (i%4==0) {
          w[i] = exp(-beta*(i-8));
        } else w[i] = 0;
      }
      Initialize_spins(spin_matrix, L, order, magnetization, energy);
      // Monte Carlo cycles
      for (int mc=0; mc<MC_steps; mc++) {
        mc_cycles_vec.push_back(mc); // proportional to time
        energy_vec.push_back(energy);
        magnet_vec.push_back(magnetization);
        metropolis(spin_matrix,L,energy,magnetization,acceptedConfigs,w);
      }
      // write file
      ofstream ofile;
      ofile.open("equiltime_"+to_string(order)+"_T"+to_string((int)temp)+".txt");
      ofile << setw(20) << "MC" << setw(20) << "E" << setw(20) << "M" << endl;
      int length = energy_vec.size();
      for (int i=0; i<length; i++) {
        ofile << setw(20) << setprecision(10) << mc_cycles_vec[i];
        ofile << setw(20) << setprecision(10) << energy_vec[i];
        ofile << setw(20) << setprecision(10) << magnet_vec[i] << endl;
      }
      ofile.close();

      // calculate the probability distribution, mean and std of the results
      vector<int> probvec = prob_distribution(energy_vec);

      ofstream ofile2;
      ofile2.open("Eprob_"+to_string(order)+"_T"+to_string((int)temp)+".txt");
      int length2 = probvec.size();
      for (int i=0; i<length2; i++) {
        ofile2 << setw(10) << setprecision(10) << probvec[i] << endl;
      }
      ofile2.close();
    }
  }
  for(int i=0; i<L; ++i) delete[] spin_matrix[i]; delete[] spin_matrix;
}

void accepted_configs(int L, int MC_steps) {
  /*
  Calculate number of accepted configurations as a function of temperature
  */
  int **spin_matrix = new int* [L];
  for (int spin=0; spin<L; spin++) spin_matrix[spin] = new int[L];
  vector<double> temp_vec;
  vector<double> accepted_vec;
  // loop over temperatures
  for (double temp = 1.0; temp<=2.4; temp+=0.05) {
    temp_vec.push_back(temp);
    // initialization
    int magnetization, energy;
    double beta = 1./temp;
    double w[17];
    for (int i=0; i<17; i++) {
      if (i%4==0) {
        w[i] = exp(-beta*(i-8));
      } else w[i] = 0;
    }
    Initialize_spins(spin_matrix, L, true, magnetization, energy);
    // Monte Carlo cycles
    int acceptedConfigs=0;
    for (int mc=0; mc<MC_steps; mc++) {
      metropolis(spin_matrix,L,energy,magnetization,acceptedConfigs,w);
    }
    accepted_vec.push_back((float)acceptedConfigs/(MC_steps-1)); // average
  }
  for(int i=0; i<L; ++i) delete[] spin_matrix[i]; delete[] spin_matrix;
  // write file
  ofstream ofile;
  ofile.open("acceptedconfigs.txt");
  ofile << setw(20) << "temp" << setw(20) << "accepted configs" << endl;
  int length = temp_vec.size();
  for (int i=0; i<length; i++) {
    ofile << setw(20) << setprecision(10) << temp_vec[i];
    ofile << setw(20) << setprecision(10) << accepted_vec[i] << endl;
  }
  ofile.close();
}

vector<int> prob_distribution(vector<int> energy_vec) {
  /* Function which computes the probability function P(E) of a lattice L=20.
  This is done for both temperatures T=1.0 and T=2.4. This probability is found
  by counting the number of times a given energy appears in the computations
  from previous results. This is done after the steady state is reached. These
  results are then compared with the computed variance in energy. */

  int total=energy_vec.size(), startVal;
  startVal = total/3;  // decide where to start counting. Should be after equilibrium.
  double mean, std, sum=0, variance=0, count=0, newSize;
  newSize = total-startVal;

  // calculate the mean and standard deviation for energy analyses.
  for (int i=startVal; i<total; i++) sum+=energy_vec[i];
  mean = sum/newSize;
  for (int i=startVal; i<total; i++) variance+=pow(energy_vec[i]-mean, 2);
  std = sqrt(variance/newSize);

  // generate a probability histogram vector with size plus minus 4*std
  vector<int> prob_histogram;

  // need to round the standard deviation and mean to the nearest +-4J
  double Emin = (mean - fmod(mean,4))-3*(std - fmod(std,4) + 4);
  // fmod replaces % for non-int values. Added four since the change is zero for std<4.
  double Emax = (mean - fmod(mean,4))+3*(std - fmod(std,4) + 4);
  // found no documentation on how to simplify this rounding to nearest 4th.
  // no solution to doubles rounding to nearest multiple of integer number

  prob_histogram.push_back(Emin);
  prob_histogram.push_back(Emax); // two first values tell about the domain.
  prob_histogram.push_back(mean);
  prob_histogram.push_back(std); // two next values tell about the distribution

  // loop the energy domain and count the number of times the energy E appears
  for (double Eval=Emin; Eval<=Emax; Eval+=4)
  {
    int counter=0;
    for (int i=startVal; i<total; i++) if (energy_vec[i]==Eval) counter++;
    prob_histogram.push_back(counter);
  }
  return prob_histogram;
}

void phase_transition() {
  /* A function which produces four plots of the mean energy <E>, mean magnetism
  <M>, heat capacity Cv and magnetic susceptibility CHI as a function of the
  temperature T. This is done for lattices L=[20, 40, 80, 100]. Parallelizing
  this code is recommended.*/
}
