#include <iostream>
#include "../include/metropolis.h"
#include "../include/spin_initializer.h"

using namespace std;

int main(int argc, char* argv[]) {

  int L=5;
  int **spin_matrix = new int* [L];
  for (int spin=0; spin<L; spin++)
  {
    spin_matrix[spin] = new int[L];
  }


  Initialize_spins(spin_matrix, L, false); // name, length and order boolean


  for (int i=0; i<L; i++){
    for (int j=0; j<L; j++){
      cout << (*spin_matrix[i]) << " ";
    }
    cout << endl;
  }




  double Tmin, Tmax;
  int MC_steps, T_step;

  // body and soul of the program
  for (double temp=Tmin; temp<=Tmax; temp+=T_step)
  {

  }




  // command line inputs
  // generate matrix

  // temperature loop
    // w
    // metropolis call

/*
    for(int i = 0; i < 5; ++i){
      delete[] p[i];//deletes an inner array of integer;
  }

  delete[] p;
  */
  return 0;
}
