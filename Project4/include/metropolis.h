#ifndef METROPOLIS_H
#define METROPOLIS_H
#include <time.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

void metropolis(int** spin_matrix, int L, double& energy, int& acceptedConfigs, double w[17]);
int energy_diff(int ix, int iy, int L, int** spin_matrix);

#endif // METROPOLIS_H
