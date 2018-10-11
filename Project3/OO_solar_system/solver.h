#ifndef SOLVER_H
#define SOLVER_H
#include <armadillo>
#include "planet.h"
#include <vector>

class solver
{
public:
  // initial values
  double dt;
  double T;
  int N = T/dt + 1;
  int number_of_planets = 0;
  vector<planet> planets_list;

  // constructor
  solver();
  solver(dt, T, system);

  // functions
  addplanet(planet name);
  velocity_verlet_solve();
  find_acc_for_all_planets(mat& acceleration_matrix);
};

#endif // SOLVER_H
