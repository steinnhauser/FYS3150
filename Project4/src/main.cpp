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
///#include <mpi.h>
#include <time.h>

using namespace std;

void lattice_solve(int L, int max_MC_steps, double temp, long idum); // finds <E>, <M>, Cv, chi vs. T
void equilibrium_time(int L, int MC_steps, long idum); // finds E(mc), M(mc)
void accepted_configs(int L, int MC_steps, long idum); // finds avg. accepted configs vs temperature
vector<int> prob_distribution(vector<int> energy_vec); //4d, find P(E) by counting #apperance of E's, L=20, T=1 and T=2.4, compare with sigma_E
void phase_transition(); //4e, 4 Plots: <E>, <M>, Cv, chi vs. T and for L=20,40,80,100

int main(int argc, char* argv[]) {
  long idum = -1; // Seed: must be negative integer

  //lattice_solve(2,10000000,1.0,idum);

  //test_initial_lattice();
  //test_energy_diff();
  equilibrium_time(20, 100000, idum);
  //accepted_configs(20, 100000, idum);


  /* parallelize the program and simulate for T=[2.0, 2.3] with dT = 0.05 or less.
  Calculate <E>, <|M|>, Cv and CHI (using <|M|>) as functions of T for lattice
  sizes L=[40, 60, 80, 100]. For post-analyses:
  Can you see an indication of a phase transition?
  Perform a timing analysis of some selected runs in order to see that you get an
  optimal speedup when parallelizing your code.

  Comment: Should in theory be four times faster (depends on computer).

  Opinion: Plot all lattice sizes in the same graph. Whole exercise is then
  compressed to a single plot which shows all the critical temperatures for each
  one of the lattice sizes L. Alternatively we could do this in four graphs.

  Opinion: Not neccesary to use an extremely large number of MC cycles. We need
  to also be able to simulate it all un-parallelized, which will take a long
  time. Also, when parallelizing, see MPI_Bcast function for communication
  between the ranks. This is not needed if say, every rank takes care of one
  temperature. This is how we should design the parallelization in my opinion.*/

  // no idea how to tell one rank to pick T=40, another T=60 etc.
  // This might need to wait until the Lab on Thursday.
  /*
  MPI_Init (&argc, &argv);
  MPI_Comm_size (MPI_COMM_WORLD, &numprocs);
  MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);

  double start, finish;
  start = clock();

  double Tmin = 2.0, Tmax = 2.3, Tstep=0.05;
  for (int L=40; L<=100; L+=20)
  {
    for (double temp=Tmin; temp<=Tmax; temp+=0.05)
    {
      lattice_solve(L, MC_steps, temp);
    }
  }
  finish = clock();
  double timeElapsed = (finish-start)/CLOCKS_PER_SEC;
  cout << "Calculation completed after " << timeElapsed << "s." << endl;
  MPI_Finalize ();
  // Run: mpirun -n 2 ./hw.x*/
  return 0;
}

void lattice_solve(int L, int max_MC_steps, double temp, long idum) {
  /*
   * Calculate expectation values for Energy and Magnetism, Heat capacity
   * and magnetic susceptibility for an LxL lattice for a given number of
   * Monte Carlo cycles and temperature
   */
  // Outer loop with various number of MC cycles: 1e1, 1e3, 1e5, 1e7
  for (int MC_steps=10; MC_steps<=max_MC_steps; MC_steps*=100) {
    double start, finish;
    start = clock();
    double avg10arr[10][6];
    // loop over 10 sample runs to generate average values
    for (int avg10=0; avg10<10; avg10++) {
      // initialization
      int **spin_matrix = new int* [L];
      for (int spin=0; spin<L; spin++) spin_matrix[spin] = new int[L];
      double magnetization=0, energy=0;
      Initialize_spins(spin_matrix, L, false, magnetization, energy, idum);
      double beta = 1./temp;
      double w[17];
      for (int i=0; i<17; i++) {
        if (i%4==0) {
          w[i] = exp(-beta*(i-8));
        } else w[i] = 0;
      }
      vector<int> energy_vec;
      vector<int> magnet_vec;
      int acceptedConfigs=0;
      double e_avg=0,e2_avg=0,m_avg=0,m2_avg=0,cv=0,chi=0;
      // Monte Carlo cycles
      for (int mc=0; mc<MC_steps; mc++) {
        energy_vec.push_back(energy);
        magnet_vec.push_back(fabs(magnetization));
        e_avg += energy;
        e2_avg += energy*energy;
        m_avg += fabs(magnetization);
        m2_avg += magnetization*magnetization;
        acceptedConfigs = 0;
        metropolis(spin_matrix,L,energy,magnetization,acceptedConfigs,w,idum);
      }
      // Save averages over 10 runs
      avg10arr[avg10][0] = (double) e_avg/MC_steps;
      avg10arr[avg10][1] = (double) e2_avg/MC_steps;
      avg10arr[avg10][2] = (double) m_avg/MC_steps;
      avg10arr[avg10][3] = (double) m2_avg/MC_steps;
      avg10arr[avg10][4] = avg10arr[avg10][1] - avg10arr[avg10][0]*avg10arr[avg10][0]; // <E^2> - <E>^2
      avg10arr[avg10][5] = avg10arr[avg10][3] - avg10arr[avg10][2]*avg10arr[avg10][2]; // <M^2> - <M>^2
      for(int i=0; i<L; ++i) delete[] spin_matrix[i]; delete[] spin_matrix;
    }
    // Compute averages
    double avgs[6];
    for (int var=0; var<6; var++){
      double val=0;
      for (int run=0; run<10; run++){
        val+=avg10arr[run][var];
      }
      avgs[var] = val/10;
    }
    // Analytic values to compute relative error
    double analytics[6] = {-7.9839, 63.8714, 3.9946, 15.9732, 0.1283, 0.016};
    cout << "10 Simulations for " << MC_steps << " MC cycles produced expectation values:" << endl;
    cout << setprecision(8) << "E:   " << avgs[0] << ". Error= " << fabs(avgs[0]-analytics[0])*1000/analytics[0] << endl;
    cout << setprecision(8) << "E^2: " << avgs[1] << ". Error= " << fabs(avgs[1]-analytics[1])*1000/analytics[1] << endl;
    cout << setprecision(8) << "M:   " << avgs[2] << ". Error= " << fabs(avgs[2]-analytics[2])*1000/analytics[2] << endl;
    cout << setprecision(8) << "M^2: " << avgs[3] << ". Error= " << fabs(avgs[3]-analytics[3])*1000/analytics[3] << endl;
    cout << setprecision(8) << "Cv:  " << avgs[4] << ". Error= " << fabs(avgs[4]-analytics[4])*1000/analytics[4] << endl;
    cout << setprecision(8) << "chi: " << avgs[5] << ". Error= " << fabs(avgs[5]-analytics[5])*1000/analytics[5] << endl << endl;

    finish = clock();
    double timeElapsed = (finish-start)/CLOCKS_PER_SEC;
    cout << "Time taken " << timeElapsed << "\n";
  }
}

void equilibrium_time(int L, int MC_steps, long idum) {
/*
 * Analyze the evolution of a 20x20 lattice for two temperatures
 * T=1.0 and T=2.4 and two initial states ordered/random.
 * Write files with: MC-cycles, Energy and Magnetization.
 */
  int **spin_matrix = new int* [L];
  for (int spin=0; spin<L; spin++) spin_matrix[spin] = new int[L];
  // loop over ordered and random initial state
  for (int order=0; order<2; order++) {
    // loop over two temperatures T=1.0 and T=2.4
    for (double temp = 1.0; temp<=2.4; temp+=1.4) {
      // initialization
      double magnetization=0;
      double energy=0;
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
      Initialize_spins(spin_matrix, L, order, magnetization, energy, idum);
      // Monte Carlo cycles
      for (int mc=0; mc<MC_steps; mc++) {
        mc_cycles_vec.push_back(mc); // proportional to time
        energy_vec.push_back(energy);
        magnet_vec.push_back(magnetization);
        metropolis(spin_matrix,L,energy,magnetization,acceptedConfigs,w,idum);
      }

      string list[3] = {"E", "M", "MC"};
      vector<int> vecs[3] = {energy_vec, magnet_vec, mc_cycles_vec};
      for (int i=0; i<3; i++){
        ofstream ofile;
        string filename="equiltime_"+to_string(order)+"_T"+to_string((int)temp)+ "_" + list[i] + ".bin";
        ofile.open("data/" + filename, ofstream::binary);
        ofile.write(reinterpret_cast<const char*> (vecs[i].data()),vecs[i].size()*sizeof(int));
        ofile.close();
      }

      // calculate the probability distribution, mean and std of the results
      vector<int> probvec = prob_distribution(energy_vec);

      ofstream ofile2;
      string filename="Eprob_"+to_string(order)+"_T"+to_string((int)temp)+".bin";
      ofile2.open("data/" + filename, ofstream::binary);
      ofile2.write(reinterpret_cast<const char*> (probvec.data()),
      probvec.size()*sizeof(int));
      ofile2.close();
      // cout << "File " << filename << " written" << "\n";

    }
  }
  for(int i=0; i<L; ++i) delete[] spin_matrix[i]; delete[] spin_matrix;
}

void accepted_configs(int L, int MC_steps, long idum) {
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
    double magnetization, energy;
    double beta = 1./temp;
    double w[17];
    for (int i=0; i<17; i++) {
      if (i%4==0) {
        w[i] = exp(-beta*(i-8));
      } else w[i] = 0;
    }
    Initialize_spins(spin_matrix, L, true, magnetization, energy, idum);
    // Monte Carlo cycles
    int acceptedConfigs=0;
    for (int mc=0; mc<MC_steps; mc++) {
      metropolis(spin_matrix,L,energy,magnetization,acceptedConfigs,w,idum);
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
 /* Function which computes the probability function P(E) of a lattice L=20,
 * for both temperatures T=1.0 and T=2.4 and initial state random/ordered.
 * The probability is found by counting the number of times a given energy
 * appears in the computations from previous results. This is done after the
 * steady state is reached. These results are then compared with the computed
 * variance in energy. */

  int total = energy_vec.size(), startVal;
  startVal = total/2; // decide where to start counting. Should be after equilibrium.
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

  /* checked whether the sum of all the energy counts were equal to the newSize.
  This was true for one case. But maybe worth to implement this as a test? */
  /* Simen: not sure whether this value newSize should be exported to normalize
  the energy counts to produce a probability distribution in post-analyses.*/
  return prob_histogram;
}

void phase_transition() {
  /* A function which produces four plots of the mean energy <E>, mean magnetism
  <M>, heat capacity Cv and magnetic susceptibility CHI as a function of the
  temperature T. This is done for lattices L=[40, 60, 80, 100]. Parallelizing
  this code is recommended.*/
}
