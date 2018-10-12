#include "initializer.h"

vector<planet> init_planet_list(string filename) {
  string line;
  vector<planet> planets_list;
  const double mass_convertion = 1e-6/1.99;

  ifstream file(filename);
  if (file.is_open()) {
    // first 7 lines
    for (int i=0; i<7; i++) {getline(file,line);}
    // the remaining lines containing planet information
    while (getline (file,line)) {
      // process line data and create one planet object into planets_list
      string name;
      double mass, x, y, z, vx, vy, vz;
      file >> name >> mass >> x >> y >> z >> vx >> vy >> vz;
      mass *= mass_convertion;
      planet planetname(mass, x, y, z, vx, vy, vz);
      planets_list.push_back(planetname);
    }
    file.close();
  }
  return planets_list;
}
