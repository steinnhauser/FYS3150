#ifndef TEST_FUNCTIONS_H
#define  TEST_FUNCTIONS_H
#include <armadillo>
using namespace arma;

void analytic_eigenvalues(mat A); //Generates analytic eigenvalues using the definition from the exercise text
double max_value_indexes(mat A, int N, int &k, int &l); // Returns indexes for max absolute value in matrix A, as (row, column)
mat generate_A_matrix(int N, vec a, vec d); //Generates the matrix A with diagonal vec d and upper and lower diagonals vec a.
void Jacobi_Rotation_algorithm(mat& A, int N, int k, int l); //Takes as an input the matrix A and S. Outputs B such that B=S^T  A   S

#endif /* TEST_FUNCTIONS_H */
