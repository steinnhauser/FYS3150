#include <iostream>
#include <armadillo>
#include <math.h>
#include "Eulers_method.h"

using namespace arma;

void Eulers_method_calculate()
{
  int N=10;
  double Simulation_Time = 1;   //One year
  double dt = Simulation_Time/N;
  const double G_MassSun = 4*M_PI*M_PI; //This has units AU^3/year^2
  vec xpos = zeros<vec>(N);
  vec xvel = zeros<vec>(N);
  vec ypos = zeros<vec>(N);
  vec yvel = zeros<vec>(N);
  vec zpos = zeros<vec>(N);
  vec zvel = zeros<vec>(N);
  double Acceleration_Earth_x, Acceleration_Earth_y, Acceleration_Earth_z, Acceleration_Earth, r;
  for (int i=0; i<(N-1); i++)
  {
    r = sqrt(xpos(i)*xpos(i) + ypos(i)*ypos(i) + zpos(i)*zpos(i));

    Acceleration_Earth = G_MassSun/(r*r);
    Acceleration_Earth_x = Acceleration_Earth*xpos(i)/r;
    Acceleration_Earth_y = Acceleration_Earth*ypos(i)/r;
    Acceleration_Earth_z = Acceleration_Earth*zpos(i)/r;

    xpos(i+1) = xpos(i) + dt*xvel(i);
    ypos(i+1) = ypos(i) + dt*yvel(i);
    zpos(i+1) = zpos(i) + dt*zvel(i);
    xvel(i+1) = xvel(i) + dt*Acceleration_Earth_x;
    yvel(i+1) = yvel(i) + dt*Acceleration_Earth_y;
    yvel(i+1) = yvel(i) + dt*Acceleration_Earth_y;
  }
  cout << "Eulers method calculation complete." << endl;
}
