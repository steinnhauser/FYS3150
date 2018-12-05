#include <vector>
#include <armadillo>

#include "functions.h"

using namespace std;
using namespace arma;

int main(int argc, char* argv[])
{
  // initial conditions

  // explicitForwardEuler(); // working.
  // implicitBackwardEuler(); // working.
  // CrankNicolsonScheme(); // working.
  JacobiMethod();



  return 0;
}
