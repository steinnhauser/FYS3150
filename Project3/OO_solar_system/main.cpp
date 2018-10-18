F #include <iostream>
#include <string>
#include <vector>
#include <armadillo>
#include "initializer.h"
#include "solver.h"
#include "planet.h"
#include "write_file.h"
#include <cmath>
#include <math.h>

using namespace std;
using namespace arma;

void mercur_perihelion_precession(cube positions, int N, double T, double dt);

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
  double T = 500*mercuryyear; // 248 = one Pluto year
  double dt = 0.000001; // unstable results when dt > 0.001
  int N = T/dt + 1;

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

  mercur_perihelion_precession(positional_tensor, N, T, dt);
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

void mercur_perihelion_precession(cube positions, int N, double T, double dt)
{
  vec time_vec = linspace<vec>(0,T,N);
  double x,y,xn,yn,rp,r,rn,angle,t;
  x = positions(0,0,1) - positions(0,0,0);
  y = positions(1,0,1) - positions(1,0,0);
  rp = sqrt(x*x + y*y);
  x = positions(0,1,1) - positions(0,1,0);
  y = positions(1,1,1) - positions(1,1,0);
  r = sqrt(x*x + y*y);

  for (int i=1; i<N-1; i++) {
    xn = positions(0,i,1) - positions(0,i,0);
    yn = positions(1,i,1) - positions(1,i,0);
    rn = sqrt(xn*xn + yn*yn);

    if (r < rn && r < rp)
    {
      x = positions(0,i-1,1);
      y = positions(1,i-1,1);
      angle = atan(y/x)*180*3600/M_PI;
      t = time_vec(i);
      cout << "perihelion, time: " << t << " angle: " << angle << endl;
    }
    x=xn;y=yn;rp=r;r=rn;
  }

  double arc_sec_century = angle*t/100; // arc sec per century
  cout << arc_sec_century << "''/century" << endl;
}
