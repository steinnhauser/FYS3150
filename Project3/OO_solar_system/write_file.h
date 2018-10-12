#ifndef WRITE_FILE_H
#define WRITE_FILE_H
#include <armadillo>
#include <fstream>
#include <vector>

void write_new_file(arma::mat positions, arma::vec time, vector<planets> planets_list);

#endif // WRITE_FILE_H
