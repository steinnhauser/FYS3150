#include<armadillo>
#include<iostream>
#include"Verlet_method.h"
using namespace arma;
using namespace std;
//Method to calculate the VELOCITY VERLET
//This Verlet method is chosen since it conserves the energy and angular momentum of the planets.
vec Verlet_method_calculate(double x0, double y0, double z0, double xv0, double yv0, double zv0, int N, double dt)
{
  const double G_MassSun = 4*M_PI*M_PI; //This has units AU^3/year^2
  vec xpos = zeros<vec>(N);
  vec ypos = zeros<vec>(N);
  vec zpos = zeros<vec>(N);
  vec xvel = zeros<vec>(N);
  vec yvel = zeros<vec>(N);
  vec zvel = zeros<vec>(N);
  xpos(0) = x0;
  ypos(0) = y0;
  zpos(0) = z0;
  xvel(0) = xv0;
  yvel(0) = yv0;
  zvel(0) = zv0;

  double Acceleration_Earth, r;
  for (int i=0; i<(N-1); i++)
  {
    //Calculate the new positions using the current velocity and acceleration
    r = sqrt(xpos(i)*xpos(i) + ypos(i)*ypos(i) + zpos(i)*zpos(i));
    Acceleration_Earth = G_MassSun/(r*r);
    double ax = Acceleration_Earth*xpos(i)/r;
    double ay = Acceleration_Earth*ypos(i)/r;
    double az = Acceleration_Earth*zpos(i)/r;

    xpos(i+1) = xpos(i) + dt*xvel(i) + dt*dt*ax/2;
    ypos(i+1) = ypos(i) + dt*yvel(i) + dt*dt*ay/2;
    zpos(i+1) = zpos(i) + dt*zvel(i) + dt*dt*az/2;

    //Calculate the velocities using the next acceleration point r(i+1)=r_New
    double r_New = sqrt(xpos(i+1)*xpos(i+1) + ypos(i+1)*ypos(i+1) + zpos(i+1)*zpos(i+1));
    double Acceleration_Earth_New = G_MassSun/(r_New*r_New);
    double ax_New = Acceleration_Earth_New*xpos(i+1)/r_New;
    double ay_New = Acceleration_Earth_New*ypos(i+1)/r_New;
    double az_New = Acceleration_Earth_New*zpos(i+1)/r_New;

    xvel(i+1) = xvel(i) + dt*(ax_New+ax)/2;
    yvel(i+1) = yvel(i) + dt*(ay_New+ay)/2;
    zvel(i+1) = zvel(i) + dt*(az_New+az)/2;
  }
  cout << "Velocity Verlet calculation complete." << endl;
  vec t = zeros<vec>(N);
  for (int i=0; i<N; i++)
  {
    t(i)=i*dt;
  }
  return xpos, ypos, zpos, t;
}
