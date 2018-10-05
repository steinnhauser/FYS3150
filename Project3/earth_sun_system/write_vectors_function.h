#ifndef Write_Vectors_H
#define Write_Vectors_H
#include <armadillo>
#include <string>
using namespace arma;
using namespace std;

void write_vectors(vec x, vec y, vec z, vec kin_energy, vec pot_energy, vec t, string fn, string title);

#endif
