// main file
// The main program is where you use the actual class.

#include "header_file.hpp"
#include <iostream>
#include <cmath>
#include <string>
#include <ctime>
#include <armadillo>
#include <fstream>

using namespace std;
using namespace arma;

#define pi 3.14159265359

int main(int argc, char *argv[]) {
  string filename = argv[1];
  double h = atof(argv[2]);
  double T_end = atof(argv[3]);
  double beta = atof(argv[4]);

  Class_name my_solver;
  my_solver.Initialize(h, T_end, filename, beta);
  my_solver.Solve();
}
