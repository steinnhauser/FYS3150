#include <iostream>
#include <string>
#include <vector>
#include <armadillo>
#include "initializer.h"
#include "solver.h"
#include "planet.h"
//#include "write_file.h"

using namespace std;

int main(int argc, char* argv[])
{
  /*
  Units used:
  1 unit of time = 1 yr
  1 unit of length = 1 AU
  1 unit of mass = 1.99*10^30 kg = 1 mass_sun
  */

  double T = 10;
  double dt = 0.1;
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
  write_file(positional_tensor, time_vec, planets_list);
  /*
  string filename = "./data/initial_values.txt";
  vector<planet*> planets_list;
  planets_list = init_planet_list(filename); // read input variables and create a vector containing planet objects
  cout << "Planet list initialized." << endl;
  cout << planets_list[0]->mass << endl;
  */


  /*
  solver(dt, totaltime, planets_list); // solve solar system simulation by using velocity verlet method
  cout << "Solver done." << endl;

  write_file(); // write files of all planet positions throughout all of the simulation period
  cout << "Files written." << endl;
  */
  return 0;
}
