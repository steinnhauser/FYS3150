#include <iostream>
#include <string>
#include <vector>
#include <armadillo>
#include "initializer.h"
#include "solver.h"
#include "planet.h"
#include "write_file.h"

using namespace std;
using namespace arma;

int main(int argc, char* argv[])
{
  /*
  Units used:
  1 unit of time = 1 yr
  1 unit of length = 1 AU
  1 unit of velocity = 1 AU/yr
  1 unit of mass = 1.99*10^30 kg = 1 mass_sun
  */

  double T = 248; // one Pluto year
  double dt = 0.0001; // unstable results when dt > 0.001
  double N = T/dt + 1;

  vector<planet> planets_list;
  string filename;
  filename = "./data/initial_values.txt";
  planets_list = init_planet_list(filename); // read input variables and create a vector containing planet objects

  int number_of_planets = planets_list.size();
  cout << "Number of integration points = " << N << endl;
  cout << "Number of planets = " << number_of_planets << endl;

  /*
  for (int j=1; j<number_of_planets; j++){
    double Etot = planets_list[j].potential_energy(planets_list[j].distance(planets_list[0]), planets_list[0]) + planets_list[j].kinetic_energy();
    cout << planets_list[j].name << "'s initial energy: " << Etot << endl;
  }
  */
  // initialize solver instance
  solver VelVerlet_Solarsystem;
  VelVerlet_Solarsystem = solver(dt, T, planets_list);
  cube positional_tensor = zeros<cube>(3,N,number_of_planets);
  cout << "Simulating Solar System..." << endl;
  // solve: most time consuming part of program
  VelVerlet_Solarsystem.velocity_verlet_solve(positional_tensor);
  /*
  cout << endl;
  for (int j=1; j<number_of_planets; j++){
    double Etot = planets_list[j].potential_energy(planets_list[j].distance(planets_list[0]), planets_list[0]) + planets_list[j].kinetic_energy();
    cout << planets_list[j].name << "'s final energy: " << Etot << endl;
  }
  */

  /*
  for (int j=0; j<number_of_planets; j++)
  {
    cout << planets_list[j].name << " mass: " << planets_list[j].mass << endl;
  }
  for (int j=1; j<number_of_planets; j++)
  {
    cout << planets_list[j].name << " distance from sun in AU: " <<  planets_list[j].distance(planets_list[0]) << endl;
  }
  */

  // study of mercury:
  number_of_planets = 2;
  vec time_vec = linspace<vec>(0,T,N);
  write_new_file(positional_tensor, time_vec, planets_list); // set to only write every 1000th data point
  cout << "Files written." << endl;

  return 0;
}
