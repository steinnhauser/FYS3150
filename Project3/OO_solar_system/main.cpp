#include <iostream>
#include <string>
#include <vector>
#include <armadillo>
#include <cmath>
#include <math.h>
#include "initializer.h"
#include "solver.h"
#include "planet.h"
#include "write_file.h"
#include "mercury.h"

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
  double mercuryyear = 0.240846;
  double T = 350; // 248 = one Pluto year
  double dt = 0.00001; // for full solar system use: <= 0.001, mercury precession: use 0.000001
  int N = T/dt + 1;
  vec time_vec = linspace<vec>(0,T,N);
  vector<planet> planets_list;
  string filename;
  filename = "./data/initial_values.txt";
  // read input variables and create a vector containing planet objects
  planets_list = init_planet_list(filename);
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
  bool sunfixed = true;
  VelVerlet_Solarsystem = solver(dt, T, planets_list, sunfixed);
  cube positional_tensor = zeros<cube>(3,N,number_of_planets);
  cout << "Simulating Solar System..." << endl;
  // solve: most time consuming part of program
  VelVerlet_Solarsystem.velocity_verlet_solve(positional_tensor);

  string filename_mercury = "./data/mercury.txt";
  mercur_perihelion_precession(positional_tensor, N, T, dt, filename_mercury);



  //write_new_file(positional_tensor, time_vec, planets_list); // set to only write every 1000th data point
  //cout << "Files written." << endl;
  /*
  for (int j=1; j<number_of_planets; j++){
    double Etot = planets_list[j].potential_energy(planets_list[j].distance(planets_list[0]), planets_list[0]) + planets_list[j].kinetic_energy();
    cout << planets_list[j].name << "'s final energy: " << Etot << endl;
  }
  */
  return 0;
}
