#include "test_functions.h"

void test_energy_conservation(vec kin_energy, vec pot_energy, string method) {
  int N = kin_energy.n_elem;
  double tot_energy_init = kin_energy(0) + pot_energy(0);
  double tot_energy_end = kin_energy(N-1) + pot_energy(N-1);
  if (fabs(tot_energy_end - tot_energy_init) > 1e-5) {
    cout << method << ", Energy/mass not conserved:" << endl;
    cout << "  start energy/mass: " << tot_energy_init << endl;
    cout << "  final energy/mass: " << tot_energy_end << endl;
  }
}

void test_angular_momentum_conservation(vec ang_mom, string method) {
  int N = ang_mom.n_elem;
  double ang_mom_init = ang_mom(0);
  double ang_mom_end = ang_mom(N-1);
  if (fabs(ang_mom_end - ang_mom_init) > 1e-5) {
    cout << method << ", Angular momentum/mass not conserved:" << endl;
    cout << "  start angular momentum/mass: " << ang_mom_init << endl;
    cout << "  final angular momentum/mass: " << ang_mom_end << endl;
  }
}
