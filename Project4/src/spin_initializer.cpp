#include "spin_initializer.h"

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
    for (int xs=0; xs<L; xs++)
    {
      for (int ys=0; ys<L; ys++)
      {
        int r=rand() % 2; // either 0 or 1
        if (r==0)
        {
          matrixname[xs][ys]=-1;
        }
        else
        {
          matrixname[xs][ys]=1;
        }
      }
    }
  }
}
