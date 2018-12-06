#include <vector>
#include <armadillo>

#include "functions.h"

using namespace std;
using namespace arma;

int main(int argc, char* argv[])
{
  // explicitForwardEuler(); // working.
  implicitBackwardEuler(); // working.
  // CrankNicolsonScheme(); // working.
  // JacobiMethod(); // working.
return 0;
}
