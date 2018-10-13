#include "solver.h"

solver::solver(){}
solver::solver(double DT, double TotalTime, std::vector<planet> Planets_List)
{
  dt = DT;
  totaltime = TotalTime;
  planets_list = Planets_List;
  number_of_planets = planets_list.size();
  N = totaltime/dt + 1;
}

void solver::velocity_verlet_solve(cube& positional_tensor)
{
  double factor2 = dt*dt/2.0;
  double factor3 = dt/2.0;
  // save initial positions in a positional tensor:
  for (int j=0; j<number_of_planets; j++){
    positional_tensor(0, 0, j) = planets_list[j].x;
    positional_tensor(1, 0, j) = planets_list[j].y;
    positional_tensor(2, 0, j) = planets_list[j].z;
  }

  for (int t=1; t<N; t++) {
    /*
    matrices acceleration_matrix_old, acceleration_matrix_new
    fill store acceleration components (ax, ay, az) for all planets which
    is the sum of all contributions from all other planets
    */
    mat acceleration_matrix_old = zeros<mat>(3,number_of_planets); // store a_t-1
    mat acceleration_matrix_new = zeros<mat>(3,number_of_planets); // store a_t
    find_acc_for_all_planets(acceleration_matrix_old, positional_tensor, t-1); // fill a_t-1 matrix

    for (int j=0; j<number_of_planets; j++)
    {
      // update x with a second degree Taylor polynomial
      positional_tensor(0, t, j) = planets_list[j].x + planets_list[j].vx*dt + factor2*acceleration_matrix_old(0, j);
      positional_tensor(1, t, j) = planets_list[j].y + planets_list[j].vy*dt + factor2*acceleration_matrix_old(1, j);
      positional_tensor(2, t, j) = planets_list[j].z + planets_list[j].vz*dt + factor2*acceleration_matrix_old(2, j);
    }

    // update positions
    for (int j=0; j<number_of_planets; j++)
    {
      planets_list[j].x = positional_tensor(0, t, j);
      planets_list[j].y = positional_tensor(1, t, j);
      planets_list[j].z = positional_tensor(2, t, j);
    }
    
    // find acceleration components at step t
    find_acc_for_all_planets(acceleration_matrix_new, positional_tensor, t);

    for (int j=0; j<number_of_planets; j++)
    {
      // update v
      planets_list[j].vx += factor3*(acceleration_matrix_new(0, j) + acceleration_matrix_old(0, j));
      planets_list[j].vy += factor3*(acceleration_matrix_new(1, j) + acceleration_matrix_old(1, j));
      planets_list[j].vz += factor3*(acceleration_matrix_new(2, j) + acceleration_matrix_old(2, j));
    }
  }
}

void solver::find_acc_for_all_planets(mat& acceleration_matrix, cube& positional_tensor, int t) {
  // p is index for current planet and op is index for other planet
  // find acceleration contribution from all other planets
  for (int p=0; p<number_of_planets; p++) {
    for (int op=0; op<number_of_planets; op++){
      // avoid finding acceleration contribution from current planet
      if (op != p) {
        double r = planets_list[p].distance(planets_list[op]);
        double acc = planets_list[p].acceleration(r, planets_list[op])/r; // total acceleration/r
        // each acceleration component: i.e -x/r * total acceleration
        acceleration_matrix(0, p) += acc * positional_tensor(0, t, p);
        acceleration_matrix(1, p) += acc * positional_tensor(1, t, p);
        acceleration_matrix(2, p) += acc * positional_tensor(2, t, p);
      }
    }
  }
}
