#ifndef WRITEFILES_H
#define WRITEFILES_H
#include <armadillo>
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;
using namespace arma;

void write_files(cube positions, vec time_vec, string method);

#endif // WRITEFILES_H
