#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <armadillo>
using namespace arma;

void analytic_eigenvalues(mat A); // Generates analytic eigenvalues using arma::eig_sym
double max_value_indexes(mat A, int N, int &k, int &l); // Returns indexes for max absolute value top triangle in matrix A, as (row, column)
mat generate_A_matrix(int N, vec a, vec d); // Generates the matrix A with diagonal vec d and upper and lower diagonals vec a.
void Jacobi_Rotation_algorithm(mat& A, int N, int k, int l); // Performs one rotation transformation in Jacobis method

#endif // FUNCTIONS_H
