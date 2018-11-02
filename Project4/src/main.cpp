#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <fstream>
#include <string>

#include "metropolis.h"
#include "spin_initializer.h"
#include "writefile.h"
//#include "mpi.h"

using namespace std;

void lattice_2x2(); //4b, <E>, <M>, Cv, chi vs. T for L=2, compare with anal, how many #mc for agreeement with uranus?
void equil_time(); //4c, ordered and random init, T=1.0 and T=2.4, plot M(mc) and E(mc) + acp vs. temp
void prob_distribution(); //4d, find P(E) by counting #apperance of a certain E, L=20, T=1 and T=2.4, compare with sigma_E
void phase_transition(); //4e, 4 Plots: <E>, <M>, Cv, chi vs. T and for L=20,40,80,100

int main(int argc, char* argv[]) {

  equil_time();
  /*
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
  // Vary temperature
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
    for (int mc=0; mc<MC_steps; mc++) {}

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

  // Vary MC cycles
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


  for (int x=0; x<L; x++) {
    for (int y=0; y<L; y++) {
      cout << spin_matrix[x][y] << " ";
    }
    cout << endl;
  }

  for(int i=0; i<L; ++i) delete[] spin_matrix[i];
  delete[] spin_matrix;

  */

  // MPI_Init (&argc, &argv);
  // MPI_Comm_size (MPI_COMM_WORLD, &numprocs);
  // MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);
  // MPI_Finalize ();
  // Run: mpirun -n 2 ./hw.x
  return 0;
}



void lattice_2x2()
{
  /* Calculate the average Energy, Magnetism, Heat capacity and magnetic
  susceptibility for a two by two lattice. Compare these with the analytical
  expressions. Analyze how many Monte Carlo cycles are required for agreement*/

  double temp = 1.0;
  int L = 2, MC_steps = 50;

  // initialize spin matrix
  int **spin_matrix = new int* [L];
  for (int spin=0; spin<L; spin++) spin_matrix[spin] = new int[L];
  int magnetization=0, energy=0;
  Initialize_spins(spin_matrix, L, true, magnetization, energy);

  double beta = 1./temp;
  double w[17];
  // fill w with Boltmann factors
  for (int i=0; i<17; i++) {
    if (i%4==0) {
      w[i] = exp(-beta*(i-8));
      cout << w[i] << endl;
    } else w[i] = 0;
  }

  vector<int> energy_vec;
  vector<int> energy2_vec;
  vector<int> magnet_vec;
  vector<int> magnet2_vec;

  int acceptedConfigs=0;

  for (int mc=0; mc<MC_steps; mc++) {
    energy_vec.push_back(energy);
    energy2_vec.push_back(energy*energy);
    magnet_vec.push_back(fabs(magnetization));
    magnet2_vec.push_back(magnetization*magnetization);
    acceptedConfigs = 0;
    metropolis(spin_matrix,L,energy,magnetization,acceptedConfigs,w);
  }

  // calculate the mean values of E, M, E^2 and M^2

  for(int i=0; i<L; ++i) delete[] spin_matrix[i];
  delete[] spin_matrix;
};

void equil_time()
{
  /* Analyze a 20 times 20 lattice. Analyze the evolution of these lattices
  for T=1.0 and T=2.4. Plot the Energy and Magnetism as functions of time (or
  Monte Carlo cycles). Do this for both ordered and random lattice initial
  conditions. Finally, analyse the following four <accepted flips> conditions:
  Nr. of Acc. Cond. for ordered or disordered at temperatures T=1 or 2.4*/

  int L = 20, MC_steps = 100;

  // first analyse the order=false case, then the order=true case
  for (int order=0; order<2; order++) {
    // initialize spin matrix
    int **spin_matrix = new int* [L];
    for (int spin=0; spin<L; spin++) spin_matrix[spin] = new int[L];
    int magnetization=0, energy=0;
    Initialize_spins(spin_matrix, L, order, magnetization, energy);

    vector<int> energy_vec;
    vector<int> magnet_vec;
    vector<int> mc_cycles_vec;
    vector<int> accepted_vec;

    // analyses of the two temperatures T=1.0 and T=2.4
    for (double temp = 1.0; temp<=2.4; temp+=1.4){
      // generate the appropriate w according to the temperature
      double beta = 1./temp;
      double w[17];
      // fill w with Boltmann factors
      for (int i=0; i<17; i++) {
        if (i%4==0) {
          w[i] = exp(-beta*(i-8));
          cout << w[i] << endl;
        } else w[i] = 0;
      }

      int acceptedConfigs=0;

      for (int mc=0; mc<MC_steps; mc++) {
        mc_cycles_vec.push_back(mc); // acts as the time axis for this research
        energy_vec.push_back(energy);
        magnet_vec.push_back(fabs(magnetization));
        accepted_vec.push_back(acceptedConfigs);
        acceptedConfigs = 0;
        metropolis(spin_matrix,L,energy,magnetization,acceptedConfigs,w);
      }
      // save the file according to the current temperature and order state
      // this file should look like E, M, acceptednr. as a function of MC step
      // format: MC, E, M, A
      ofstream ofile;
      string tempstring;
      if(temp==1.0){tempstring="1";}else{tempstring="2";}
      ofile.open("datafile_" + to_string(order) + "_T" + tempstring + ".txt");
      ofile << setw(20) << "MC" << setw(20) << "E";
      ofile << setw(20) << "M" << setw(20) << "Accepted" << endl;

      int length = energy_vec.size();

      for (int i=0; i<length; i++)
      {
        ofile << setw(20) << setprecision(10) << mc_cycles_vec[i];
        ofile << setw(20) << setprecision(10) << energy_vec[i];
        ofile << setw(20) << setprecision(10) << magnet_vec[i];
        ofile << setw(20) << setprecision(10) << accepted_vec[i] << endl;
      }
      ofile.close();
      Initialize_spins(spin_matrix, L, order, magnetization, energy);
    }

    for(int i=0; i<L; ++i) delete[] spin_matrix[i];
    delete[] spin_matrix;
  }
  // name of files should be datafile_ordered_1.txt, datafile_ordered_24.txt,
  // datafile_random_1.txt and datafile_random_24.txt
};
void prob_distribution()
{
  /* Function which computes the probability function P(E) of a lattice L=20.
  This is done for both temperatures T=1.0 and T=2.4. This probability is found
  by counting the number of times a given energy appears in the computations
  from previous results. This is done after the steady state is reached. These
  results are then compared with the computed variance in energy. */
};

void phase_transition()
{
  /* A function which produces four plots of the mean energy <E>, mean magnetism
  <M>, heat capacity Cv and magnetic susceptibility CHI as a function of the
  temperature T. This is done for lattices L=[20, 40, 80, 100]. Parallelizing
  this code is recommended.*/
};
