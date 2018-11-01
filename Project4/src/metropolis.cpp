#include "metropolis.h"

void metropolis(int** spin_matrix, int L) {
  /*
  Performs on Monte Carlo sweep of the lattice.
  - Random indices [ix][iy] are chosen each iteration
  - Energy difference (when spin[ix][iy] is flipped) is found using energy_diff()
  - Accept or decline move according to Metropolis algorithm
  */
  for (int x=0; x<L; x++) {
    for (int y=0; y<L; y++) {
      // choose random indices


    }
  }
}

int energy_diff(int ix, int iy) {
  /*
  Calulate energy difference if spin at position ix,iy is flipped.
  Takes care of periodic boundary conditions
  */
  int dE = 2*( )

}
