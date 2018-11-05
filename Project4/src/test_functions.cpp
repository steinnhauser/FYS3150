#include "test_functions.h"

void test_initial_lattice() {
  int L = 2;
  int **spin_matrix = new int* [L];
  for (int spin=0; spin<L; spin++) spin_matrix[spin] = new int[L];
  double magnetization=0;
  double energy=0;
  Initialize_spins(spin_matrix, L, true, magnetization, energy);
  if (energy != -8) {
    cout << "Initial energy: " << energy << " is wrong!" << endl;
  }
  if (magnetization != 4) {
    cout << "Initial magnetization: " << magnetization << " is wrong!" << endl;
  }
}
