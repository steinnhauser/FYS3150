#include "initializer.h"
#include "planet.h"

vector<planet> init_planet_list(string filename) {
  string line;
  vector<planet> planets_list;
  const double mass_convertion = 1.0/(1.99e6); // from 10^24 kg to sun masses
  const double vel_convertion = 365.25;
  ifstream file(filename);
  if (file.is_open()) {
    // first 7 lines
    for (int i=0; i<6; i++) {getline(file,line);}
    // the remaining lines containing planet information
    while (getline (file,line)) {
      // process line data and create one planet object into planets_list
      string name;
      double mass, x, y, z, vx, vy, vz;
      file >> name >> mass >> x >> y >> z >> vx >> vy >> vz;
      mass *= mass_convertion;
      vx *= vel_convertion;
      vy *= vel_convertion;
      vz *= vel_convertion;
      planet planetName;
      planetName = planet(mass, x, y, z, vx, vy, vz);
      planetName.setName(name);
      planets_list.push_back(planetName);
    }
    planets_list.pop_back(); // last element is empty
    file.close();
  }
  return planets_list;
}
