#include "mercury.h"

void mercur_perihelion_precession(cube positions, int N, double T, double dt, string filename)
{
  vec time_vec = linspace<vec>(0,T,N);
  double x,y,xn,yn,rp,r,rn,angle,t;
  x = positions(0,0,1) - positions(0,0,0);
  y = positions(1,0,1) - positions(1,0,0);
  rp = sqrt(x*x + y*y);
  x = positions(0,1,1) - positions(0,1,0);
  y = positions(1,1,1) - positions(1,1,0);
  r = sqrt(x*x + y*y);
  vector<double> times;
  vector<double> angles;

  // loop over time to find times/angle at perhelion
  for (int i=1; i<N-1; i++)
  {
    xn = positions(0,i,1) - positions(0,i,0);
    yn = positions(1,i,1) - positions(1,i,0);
    rn = sqrt(xn*xn + yn*yn);
    // if test passes, i-1 was a perihelion point
    if (r < rn && r < rp)
    {
      x = positions(0,i-1,1);
      y = positions(1,i-1,1);
      angles.push_back(atan(y/x)*180*3600/M_PI);
      times.push_back(time_vec(i));
    }
    x=xn;y=yn;rp=r;r=rn;
  }
  ofstream ofile;
  ofile.open(filename, ofstream::out | ofstream::trunc);

  // Linear regression for angle/time:
  double n = angles.size();
  for(int i=0; i<n; i++)
  {
    ofile << setw(20) << setprecision(10) << times[i];
    ofile << setw(20) << setprecision(10) << angles[i] << endl;
  }
  ofile.close();
  double avg_time = accumulate(times.begin(), times.end(), 0.0) / n;
  double avg_angle = accumulate(angles.begin(), angles.end(), 0.0) / n;
  double top = 0.0;
  double bottom = 0.0;
  for(int i=0; i<n; i++)
  {
    top += (times[i] - avg_time) * (angles[i] - avg_angle);
    bottom += (times[i] - avg_time) * (times[i] - avg_time);
    cout << angles[i] << endl;
  }
  double slope = top/bottom*100; // arc sec per century
  cout << "perihelion precession: " << slope << "''/century" << endl;
}
