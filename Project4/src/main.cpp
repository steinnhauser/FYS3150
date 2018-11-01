#include <iostream>
#include <cmath>
#include "metropolis.h"
#include "spin_initializer.h"

using namespace std;

int main(int argc, char* argv[]) {

  int L = 5;
  int **spin_matrix = new int* [L];
  for (int spin=0; spin<L; spin++) spin_matrix[spin] = new int[L];

  // initialize spin_matrix: name, length and order: true=ordered, false=random
  Initialize_spins(spin_matrix, L, false);

  double Tmin = 1;
  double Tmax = 2.4;
  int MC_steps = 5;
  int T_step = 1;
  double w[17]; // Boltzmann factors of energy levels -8J to 8J

  // body and soul of the program
  for (double temp=Tmin; temp<=Tmax; temp+=T_step) {
    // initialize w
    double beta = 1./temp;
    for (int i=0; i<17; i++) {
      if (i%4==0) {
        w[i] = exp(-beta*(i-8));
      } else w[i] = 0;
    }
    // MC cycles
    double energy = 0;
    int acceptedConfigs = 0;
    for (int mc=0; mc<MC_steps; mc++) {
      metropolis(spin_matrix,L,energy,acceptedConfigs,w);
    }
    // Save E(T), save #MC, save acceptedConfigs(T)
    /*for (int i=0; i<17; i++) {
      cout << w[i] << endl;
    }*/
  }

  for(int i=0; i<L; ++i) delete[] spin_matrix[i];
  delete[] spin_matrix;

  return 0;
}
