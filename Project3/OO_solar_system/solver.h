#ifndef SOLVER_H
#define SOLVER_H
#include <armadillo>
#include <vector>
#include "planet.h"

using namespace arma;

class solver
{
public:
  // initial values
  const double dt;
  const double totaltime;
  const int N = totaltime/dt + 1;
  int number_of_planets = 0;
  std::vector<planet> planets_list;

  // constructor
  solver();
  solver(const double dt, const double totaltime);

  // functions
  void addplanet(planet name);
  void velocity_verlet_solve();
  void find_acc_for_all_planets(mat& acceleration_matrix);
};

#endif // SOLVER_H
