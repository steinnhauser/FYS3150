#ifndef MERCURY_H
#define MERCURY_H
#include <iostream>
#include <iomanip>
#include <fstream>
#include <armadillo>
#include <vector>
#include <string>

using namespace std;
using namespace arma;

void mercur_perihelion_precession(cube positions, int N, double T, double dt, string filename);

#endif // MERCURY_H
