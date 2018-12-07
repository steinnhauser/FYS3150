#include <vector>
#include <armadillo>
#include "functions.h"

int main(int argc, char* argv[])
{
  // 1D functions called with (nx, nt, dx, dt)
  // dx = 0.1:
  int nx=10;
  int nt=1000;
  double dx=0.1;
  double dt=0.001;
  // explicitForwardEuler(nx, nt, dx, dt,"data/dx01/ex.bin");
  // implicitBackwardEuler(nx, nt, dx, dt,"data/dx01/im.bin");
  // CrankNicolsonScheme(nx, nt, dx, dt,"data/dx01/cn.bin");
  analytic1D(nx, dx, "data/dx01/an.bin");
  // dx = 0.01:
  int nx2=100;
  int nt2=100000;
  double dx2=0.01;
  double dt2=0.00001;
  // explicitForwardEuler(nx2, nt2, dx2, dt2,"data/dx001/ex.bin");
  // implicitBackwardEuler(nx2, nt2, dx2, dt2,"data/dx001/im.bin");
  // CrankNicolsonScheme(nx2, nt2, dx2, dt2,"data/dx001/cn.bin");
  analytic1D(nx2, dx2, "data/dx001/an.bin");

  // JacobiMethod();

  return 0;
}
