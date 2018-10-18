#include <iostream>
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
  double T = 1000*mercuryyear; // 248 = one Pluto year
  double dt = 0.00001; // for full solar system use: <= 0.001, mercury precession: use 0.000001
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
  vector<double> times;
  vector<double> angles;

  for (int i=1; i<N-1; i++)
  {
    xn = positions(0,i,1) - positions(0,i,0);
    yn = positions(1,i,1) - positions(1,i,0);
    rn = sqrt(xn*xn + yn*yn);
    // if test passes, i-1 was a perihelion point
    if (r < rn && r < rp)
    {
      x = positions(0,i-1,1);
      y = positions(1,i-1,1);
      angles.push_back(atan(y/x)*180*3600/M_PI);
      times.push_back(time_vec(i));
    }
    x=xn;y=yn;rp=r;r=rn;
  }

  // Linear regression for angle/time:
  double n = angles.size();
  double avg_time = accumulate(times.begin(), times.end(), 0.0) / n;
  double avg_angle = accumulate(angles.begin(), angles.end(), 0.0) / n;
  double top = 0.0;
  double bottom = 0.0;
  for(int i=0; i<n; i++)
  {
    top += (times[i] - avg_time) * (angles[i] - avg_angle);
    bottom += (times[i] - avg_time) * (times[i] - avg_time);
  }
  double slope = top/bottom*100; // arc sec per century
  cout << "perihelion precession: " << slope << "''/century" << endl;
}
