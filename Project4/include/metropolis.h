#ifndef METROPOLIS_H
#define METROPOLIS_H
#include <time.h>
#include <stdlib.h>

void metropolis(int** spin_matrix, int L);
int energy_diff(int ix, int iy, int L, int** spin_matrix);

#endif // METROPOLIS_H
