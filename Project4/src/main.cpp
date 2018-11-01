#include <iostream>
#include "metropolis.h"
#include "spin_initializer.h"
#include <cmath>

using namespace std;

int main(int argc, char* argv[]) {

  int L = 5;
  int **spin_matrix = new int* [L];
  for (int spin=0; spin<L; spin++) spin_matrix[spin] = new int[L];

  //
  Initialize_spins(spin_matrix, L, false); // name, length and order: true=ordered, false=random


  double Tmin, Tmax;
  int MC_steps, T_step;

  const double k = 1.381e-23;

  // body and soul of the program
  for (double temp=Tmin; temp<=Tmax; temp+=T_step) {
    double beta = 1./(k*temp);
    double *w = new double [17]; // Boltzmann factors of energy levels -8J to 8J
    for (int i=0; i<17; i++)
    {
      if (i%4==0)
      {
        w[i]=exp(-beta*(i-8));
      } else w[i] = 0;
    }

    for (int i=0; i<17; i++)
    {
      cout << w[i] << endl;
    }

    // metropolis call
  }

  for(int i=0; i<L; ++i) delete[] spin_matrix[i];
  delete[] spin_matrix;

  return 0;
}
