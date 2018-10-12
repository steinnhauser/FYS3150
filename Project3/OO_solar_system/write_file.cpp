#include "write_file.h"

void write_new_file(arma::mat positions, arma::vec time, vector<planets*> planets_list)
{
  // assuming matrix with the form positions(3, N, j);
  string FN = "./data/";
  string fn = "test_system"
  FN.append(fn + ".txt");
  ofstream ofile;
  ofile.open(FN, std::ofstream::out | std::ofstream::trunc);
  for (int j=0; j<number_of_planets; j++){
    // write name of planet
    string title;
    title = planets_list[j].name;

    ofile << title << endl;
    ofile << setw(20) << "x: " << setw(20) << "y: " << setw(20) << "z: ";
    ofile << setw(20) << "t: " << endl;

    for (int t=0; t<N; t++){
      ofile << setw(20) << setprecision(10) << positions(0, t, j);
      ofile << setw(20) << setprecision(10) << positions(1, t, j);
      ofile << setw(20) << setprecision(10) << positions(2, t, j);
      ofile << setw(20) << setprecision(10) << time(t);

      //write file with these

    }
  }
  ofile.close();
  cout << "File " << FN << " written." << endl;
}



/*
else{
    //string filename = "./data/project2_";
    //filename.append(to_string(j) + ".txt");
    string FN = "./data/";
    FN.append(fn + ".txt");
    ofstream ofile;
    ofile.open(FN, std::ofstream::out | std::ofstream::trunc);

    ofile << title << endl;
    ofile << setw(20) << "x: " << setw(20) << "y: " << setw(20) << "z: ";
    ofile << setw(20) << "Ek:" << setw(20) << "Ep:" << setw(20) << "t: " << endl;

    int Length = x.n_elem;
    for (int i=0; i<Length; i++) {
      ofile << setw(20) << setprecision(10) << x(i);
      ofile << setw(20) << setprecision(10) << y(i);
      ofile << setw(20) << setprecision(10) << z(i);
      ofile << setw(20) << setprecision(10) << kin_energy(i);
      ofile << setw(20) << setprecision(10) << pot_energy(i);
      ofile << setw(20) << setprecision(10) << t(i) << endl;
    }
    ofile.close();
    cout << "File " << FN << " written." << endl;
  }
*/
