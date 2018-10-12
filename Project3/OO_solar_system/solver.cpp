#include "solver.h"

void solver::addplanet(planet name)
{
  planets_list.push_back(name);
  number_of_planets++;
}

void solver::velocity_verlet_solve()
{
  double factor2 = dt*dt/2.0;
  double factor3 = dt/2.0;

  for (int t=0; t<N; t++) {
    /*
    matrices acceleration_matrix_old, acceleration_matrix_new
    fill store acceleration components (ax, ay, az) for all planets which
    is the sum of all contributions from all other planets
    */
    mat acceleration_matrix_old = zeros<mat>(3,number_of_planets); // store a_t
    mat acceleration_matrix_new = zeros<mat>(3,number_of_planets); // store a_t+1
    find_acc_for_all_planets(acceleration_matrix_old); // fill a_t matrix

    for (int j=0; j<number_of_planets; j++) {

      // find acceleration components at step t
      double ax = acceleration_matrix_old(0, j);
      double ay = acceleration_matrix_old(1, j);
      double az = acceleration_matrix_old(2, j);

      // update x with a second degree Taylor polynomial
      planets_list[j].x += planets_list[j].vx*dt + factor2*ax;
      planets_list[j].y += planets_list[j].vy*dt + factor2*ay;
      planets_list[j].z += planets_list[j].vz*dt + factor2*az;

      // find acceleration components at step t+1
      find_acc_for_all_planets(acceleration_matrix_new);

      double ax_new = acceleration_matrix_new(0, j);
      double ay_new = acceleration_matrix_new(1, j);
      double az_new = acceleration_matrix_new(2, j);

      // update v
      planets_list[j].vx += factor3*(ax + ax_new);
      planets_list[j].vy += factor3*(ay + ay_new);
      planets_list[j].vz += factor3*(az + az_new);
    }
  }
}

void solver::find_acc_for_all_planets(mat& acceleration_matrix) {
  // p is index for current planet and op is index for other planet
  // find acceleration contribution from all other planets
  for (int p=0; p<number_of_planets; p++) {
    for (int op=0; op<number_of_planets; op++){
      // avoid finding acceleration contribution from current planet itself
      if (op != p) {
        double r = planets_list[p].distance(planets_list[op]);
        double acc = planets_list[p].acceleration(r, planets_list[op])/r; // total acceleration/r
        // each acceleration component: i.e -x/r * total acceleration
        acceleration_matrix(0, p) += acc * planets_list[p].x;
        acceleration_matrix(1, p) += acc * planets_list[p].y;
        acceleration_matrix(2, p) += acc * planets_list[p].z;
      }
    }
  }
}
