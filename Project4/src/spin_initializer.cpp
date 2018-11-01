#include "../include/spin_initializer.h"
#include <iostream>

void Initialize_spins(int** matrixname, int L, bool order)
{
  if (order==true){ // ordered matrix elements equal to 1
    for (int xs=0; xs<L; xs++)
    {
      for (int ys=0; ys<L; ys++)
      {
        matrixname[xs][ys]=1;
      }
    }
  } else { // initialize a random-spin matrix
    srand(time(NULL));
    int r;
    for (int xs=0; xs<L; xs++)
    {
      for (int ys=0; ys<L; ys++)
      {
        r=rand() % 2; // either 0 or 1
        std::cout << r << std::endl;
        if (r==1)
        {
          matrixname[xs][ys]=1;
        }
        else
        {
          matrixname[xs][ys]=-1;
        }
      }
    }
  }
}
