// main file
// The main program is where you use the actual class.

#include "header_file.hpp"
#include <iostream>
#include <cmath>
#include <string>
#include <ctime>
#include <armadillo>

using namespace std;
using namespace arma;

double Buck_beam(double rho_i, double omega_r);
double pot_1e(double rho_i, double omega_r);
double pot_2e(double rho_i, double omega_r);

//double omega_r = 0.01;
//double omega_r = 0.5;
//double omega_r = 1.;
//double omega_r = 5.;

double omega_r = 0.;

int main(int argc, char *argv[]) {
  //Parameters
  int n = 350;
  string filename = "data.txt";
  //string filename = "data_1000.txt";
  double rho_max = atof(argv[1]); //vil at omega_r skal bli tatt som et argument
  string outfilename = argv[2];


  Class_name my_solver; //initiate class
  my_solver.Initialize(n, pot_1e, omega_r, rho_max);
  my_solver.Solver();
  my_solver.Unit_test();
  //my_solver.Write_to_file(filename);
  my_solver.rel_err_rho_max(outfilename);
  return 0;
}

double Buck_beam(double rho_i, double omega_r){
  return 0;
}

double pot_1e(double rho_i, double omega_r){
  return rho_i*rho_i;
}

double pot_2e(double rho_i, double omega_r){
  return pow(omega_r,2)*pow(rho_i,2) + 1/rho_i;
}