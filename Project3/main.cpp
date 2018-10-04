#include <iostream>
#include <string>
#include "Eulers_method.h"
#include "Verlet_method.h"
#include "Write_Vectors_function.h"
using namespace std;
using namespace arma;

int main(int argc, char* argv[])
{
  Eulers_method_calculate();
  Verlet_method_calculate();
  vec x = zeros<vec>(10);
  vec y = zeros<vec>(10);
  vec z = zeros<vec>(10);
  vec t = zeros<vec>(10);
  string f, title;
  f = "Testfile.txt";
  title = "Testtitle";
  Write_Vectors(x, y, z, t, f, title);
  return 0;
}
