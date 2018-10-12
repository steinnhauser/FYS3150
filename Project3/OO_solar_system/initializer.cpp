#include "planet.h"
#include "initializer.h"
using namespace std;

void init_planet_list(string filename) {
  ifstream file(filename);
  string line;
  if (file.is_open())
  {
    // first 7 lines
    for (int i=0; i<7; i++) {getline(file,line);}
    // the remaining lines containing planet information
    while (getline (file,line))
    {
      cout << line << '\n';
    }
    file.close();
  }
}
