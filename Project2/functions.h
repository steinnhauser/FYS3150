#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <armadillo>
using namespace arma;

void analytic_eigenvalues(mat A); // Generates analytic eigenvalues using arma::eig_sym
double max_value_indexes(mat A, int N, int &k, int &l); // Returns indexes for max absolute value top triangle in matrix A, as (row, column)
mat generate_A_matrix(int N, vec a, vec d); // Generates the matrix A with diagonal vec d and upper and lower diagonals vec a.
void Jacobi_Rotation_algorithm(mat& A, mat& R, int N, int k, int l); // Performs one rotation transformation in Jacobi's method
void find_lowest_eigval_eigvec_pair(double& eigval, vec& eigvec, mat A, mat R, int N); // finding the first eigenpair and verifying that it's correct

#endif // FUNCTIONS_H
