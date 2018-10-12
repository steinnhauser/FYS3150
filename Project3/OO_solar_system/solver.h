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
  double dt;
  double totaltime;
  int N = totaltime/dt + 1;
  std::vector<planet> planets_list;
  int number_of_planets = planets_list.size();

  // constructor
  solver();
  solver(double DT, double TotalTime, std::vector<planet> Planets_List);

  // functions
  void velocity_verlet_solve();
  void find_acc_for_all_planets(mat& acceleration_matrix);
};

#endif // SOLVER_H
