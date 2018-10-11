#include <iostream>
#include <string>
#include <math.h>
#include "planet.h"
#include "eulers_method.h"
#include "verlet_method.h"
#include "write_vectors_function.h"

using namespace arma;

int main(int argc, char* argv[])
{
  double T = 10;
  double dt = 0.0001;
  int N = T/dt + 1;


  planet earth(initial_values...);

  return 0;
}
