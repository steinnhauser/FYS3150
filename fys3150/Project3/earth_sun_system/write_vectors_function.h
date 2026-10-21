#ifndef WRITE_VECTORS_FUNCTION_H
#define WRITE_VECTORS_FUNCTION_H
#include <armadillo>
#include <string>
#include <iomanip>
#include <iostream>
using namespace arma;
using namespace std;

void write_vectors(vec x, vec y, vec z, vec kin_energy, vec pot_energy, vec ang_mom, vec t, string fn, string title);

#endif // WRITE_VECTORS_FUNCTION_H
