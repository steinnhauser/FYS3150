#include <iostream>
#include <string>
#include <math.h>
#include "Eulers_method.h"
#include "Verlet_method.h"
#include "Write_Vectors_function.h"
using namespace std;
using namespace arma;

int main(int argc, char* argv[])
{
  int N=10;
  double dt = 1/10;

  double x0 = 1; //Trying with 1AU
  double y0 = 0;
  double z0 = 0;
  double xv0 = 0;
  double yv0 = 2*M_PI; //One rotation per year
  double zv0 = 0;

  vec x1; vec y1; vec z1; vec t1;
  //vec x2; vec y2; vec z2; vec t2;

  Eulers_method_calculate(x0, y0, z0, xv0, yv0, zv0, N, dt, x1, y1, z1, t1);
  //x2, y2, z2, t2 = Verlet_method_calculate(x0, y0, z0, xv0, yv0, zv0, N, dt );

  //x1.print();
  //y1.print();
  //z1.print();
  //t1.print();

  string f, title;
  f = "Eulerfile";
  title = "Euler simulation";
  Write_Vectors(x1, y1, z1, t1, f, title);
  //f = "Verletfile";
  //title = "Verlet simulation";
  //Write_Vectors(x2, y2, z2, t2, f, title);
  return 0;
}
