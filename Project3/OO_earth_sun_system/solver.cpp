#include "solver.h"
#include <vector>
#include <string>
#include <armadillo>

using namespace arma;

void addplanet(planet name)
{
  planets_list.push_back(name);

  number_of_planets++;
}

void velocity_verlet_solve();
{

  for (int t = 0; t < N; t++) {
    mat acceleration_matrix_old = zeros<mat>(3,number_of_planets - 1);
    mat acceleration_matrix_new = zeros<mat>(3,number_of_planets - 1);
    find_acc_for_all_planets(acceleration_matrix_old);


    for (int j = 0; j < number_of_planets; j++) {
      currentplanet = planets_list[j];
      //method(planet1, planet2)

      double ax = acceleration_matrix(0, j);
      double ay = acceleration_matrix(1, j);
      double az = acceleration_matrix(2, j);

      //update x
      x_pos(i+1) = x_pos(i) + dt*x_vel(i) + factor2*x_acc;
      y_pos(i+1) = y_pos(i) + dt*y_vel(i) + factor2*y_acc;
      z_pos(i+1) = z_pos(i) + dt*z_vel(i) + factor2*z_acc;

      //Fill acceleration_matrix_new
      find_acc_for_all_planets(acceleration_matrix_new);

      double ax_new = acceleration_matrix_new(0, j);
      double ay_new = acceleration_matrix_new(1, j);
      double az_new = acceleration_matrix_new(2, j);

      //update v
      x_vel(i+1) = x_vel(i) + factor3*(x_acc + x_acc_new);
      y_vel(i+1) = y_vel(i) + factor3*(y_acc + y_acc_new);
      z_vel(i+1) = z_vel(i) + factor3*(z_acc + z_acc_new);
    }
  }
}

void find_acc_for_all_planets(mat& acceleration_matrix)
  {
    const double Gfactor = ;
    double r_squared, factor1;
    double factor2 = dt*dt/2.0;
    double factor3 = dt/2.0;

    for (int p=0; p<number_of_planets; p++) {
      for (int op=0; op<number_of_planets; op++){
        if (op != p) {
          double r = planets_list[p].distance(planets_list[op]);
          double acc = planets_list[p].acceleration(planets_list[op]);
          acceleration_matrix(0, p)= acc * planets_list[p].x/r;
          acceleration_matrix(1, p)= acc * planets_list[p].y/r;
          acceleration_matrix(2, p)= acc * planets_list[p].z/r;
        }
      }

}
