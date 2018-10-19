#ifndef TEST_FUNCTIONS_H
#define  TEST_FUNCTIONS_H
#include <armadillo>
#include <iostream>
#include <cmath>
#include <string>
using namespace arma;
using namespace std;

void test_energy_conservation(vec kin_energy, vec pot_energy, string method);
void test_angular_momentum_conservation(vec ang_mom, string method);

#endif // TEST_FUNCTIONS_H
