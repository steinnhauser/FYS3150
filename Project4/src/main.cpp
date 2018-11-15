#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <fstream>
#include <string>
#include <mpi.h>
#include <time.h>

#include "metropolis.h"
#include "spin_initializer.h"
#include "test_functions.h"
#include "functions.h"

using namespace std;

int main(int argc, char* argv[]) {
  long idum = -10; // RNG seed: negative integer
  // finds expectation values for 10^1, 10^3, 10^5 ,... MC cycles
  // lattice_solve_2x2(10000000,1.0,idum);
  test_initial_lattice();
  test_energy_diff();
  // equilibrium_time(20, 10000, idum);
  accepted_configs(20, 10000, idum);
  /*
  int numprocs, my_rank;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  int MCS = 100000;
  ofstream ofile;
  bool fileBool=true;

  for (int L=40; L<=100; L+=20) {
    double start, finish;
    start = clock();

    if (my_rank==0) cout << "-----\nL: " << L << "\n";
    int MC_steps = MCS/numprocs;
    int equil = 250*L;
    long idum = - 1 - my_rank;
    double data_vec[4]={0};
    double allocate[4]={0};

    vector<double> temp_vec;
    for (double t=2.1; t<=2.2; t+=0.05) temp_vec.push_back(t);
    for (double t=2.21; t<=2.26; t+=0.01) temp_vec.push_back(t);
    for (double t=2.261; t<=2.28; t+=0.001) temp_vec.push_back(t);
    for (double t=2.29; t<=2.32; t+=0.01) temp_vec.push_back(t);
    for (double t=2.37; t<=2.57; t+=0.05) temp_vec.push_back(t);

    double temp;
    int N = temp_vec.size();
    for (int i=0; i<N; i++) {
      temp = temp_vec[i];
      double e_avg=0, e2_avg=0, m_avg=0, m2_avg=0;
      phase_transition(L, temp, equil, e_avg, e2_avg, m_avg, m2_avg, MC_steps, idum); // MCsteps: equil + MC_steps
      data_vec[0] = e_avg;
      data_vec[1] = e2_avg;
      data_vec[2] = m_avg;
      data_vec[3] = m2_avg;

      for (int i=0; i<4; i++){
        MPI_Reduce(&data_vec[i], &allocate[i], 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
      }

      if (my_rank==0){
        cout << "Temperature T=" << temp << "\n";
        for (int i=0; i<4; i++){
          allocate[i] /= numprocs; //Normalize properly.
          allocate[i] /= L*L; //Make it "Per atom spin"
        }
      }

      //Write files traditionally. Only open the file for the first temperature
      //and close the file once the temperature loop is completed. This is done
      //for every lattice size desired.

      if (my_rank==0 && fileBool==true){
        string filename = "./data/lattice_";
        filename.append(to_string(L) + ".txt");
        ofile.open(filename, std::ofstream::out | std::ofstream::trunc);
        ofile << setw(20) << "T:" << setw(20) << "E:" << setw(20) << "E^2: ";
        ofile << setw(20) << "M:" << setw(20) << "M^2: " << endl;

        ofile << setw(20) << setprecision(10) << temp;
        ofile << setw(20) << setprecision(10) << allocate[0];
        ofile << setw(20) << setprecision(10) << allocate[1];
        ofile << setw(20) << setprecision(10) << allocate[2];
        ofile << setw(20) << setprecision(10) << allocate[3] << endl;

        fileBool=false;
      }
      else if (my_rank==0){
        ofile << setw(20) << setprecision(10) << temp;
        ofile << setw(20) << setprecision(10) << allocate[0];
        ofile << setw(20) << setprecision(10) << allocate[1];
        ofile << setw(20) << setprecision(10) << allocate[2];
        ofile << setw(20) << setprecision(10) << allocate[3] << endl;
      }
    }
    ofile.close();
    fileBool=true;
    if (my_rank==0){
      finish = clock();
      double timeElapsed = (finish-start)/CLOCKS_PER_SEC;
      cout << "L: " << L << " calculation completed after " << timeElapsed << "s." << endl;
    }
  }
  MPI_Finalize();*/
  return 0;
}
