#include <vector>
#include <armadillo>
#include "functions.h"

int main(int argc, char* argv[])
{
  // 1D functions called with (nx, nt, dx, dt)
  // dx = 0.1:
  // explicitForwardEuler(10,1000,0.1,0.001,"data/dx01/ex.bin");
  implicitBackwardEuler(10,1000,0.1,0.001,"data/dx01/im.bin");
  CrankNicolsonScheme(10,1000,0.1,0.001,"data/dx01/cn.bin");
  // analytic1D(10,1000,0.1,0.001,"data/dx01/an.bin");
  // dx = 0.01, note: nt is larger for explicit (alpha <= 0.5)
  // explicitForwardEuler(100,100000,0.01,0.00001,"data/dx001/ex.bin");
  implicitBackwardEuler(100,1000,0.01,0.001,"data/dx001/im.bin");
  CrankNicolsonScheme(100,1000,0.01,0.001,"data/dx001/cn.bin");
  // analytic1D(100,1000,0.01,0.001,"data/dx001/an.bin");

  // JacobiMethod();

  return 0;
}
