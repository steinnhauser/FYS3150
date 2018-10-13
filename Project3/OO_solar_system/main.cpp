#include <iostream>
#include <string>
#include <vector>
#include <armadillo>
#include "initializer.h"
#include "solver.h"
#include "planet.h"
#include "write_file.h"

using namespace std;

int main(int argc, char* argv[])
{
  /*
  Units used:
  1 unit of time = 1 yr
  1 unit of length = 1 AU
  1 unit of velocity = 1 AU/yr
  1 unit of mass = 1.99*10^30 kg = 1 mass_sun
  */

  double T = 30;
  double dt = 0.001;
  double N = T/dt + 1;

  vector<planet> planets_list;
  string filename;
  filename = "./data/initial_values.txt";
  planets_list = init_planet_list(filename); // read input variables and create a vector containing planet objects


  int number_of_planets = planets_list.size();


  solver VelVerlet_Solarsystem;
  VelVerlet_Solarsystem = solver(dt, T, planets_list);

  arma::cube positional_tensor = zeros<cube>(3,N,number_of_planets);
  VelVerlet_Solarsystem.velocity_verlet_solve(positional_tensor);

  arma::vec time_vec = linspace<vec>(0,T,N);
  write_new_file(positional_tensor, time_vec, planets_list);
  cout << "Files written." << endl;

  return 0;
}
