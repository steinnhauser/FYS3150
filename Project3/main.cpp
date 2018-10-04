#include <iostream>
#include "Eulers_method.h"
#include "Verlet_method.h"
#include "Write_Vectors_file.h"
using namespace std;

int main(int argc, char* argv[])
{
  Eulers_method_calculate();
  Verlet_method_calculate();
  return 0;
}
