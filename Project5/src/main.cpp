#include <vector>
#include <armadillo>
#include "functions.h"

int main(int argc, char* argv[])
{
  // explicitForwardEuler(); // working.
  // implicitBackwardEuler(); // working.
  // CrankNicolsonScheme(); // working.
  JacobiMethod(); // working.
  
  return 0;
}
