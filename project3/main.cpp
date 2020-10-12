// main file
// The main program is where you use the actual class.

#include "header_file.hpp"
#include "method.cpp"
#include <iostream>
#include <cmath>
#include <string>
#include <ctime>
#include <armadillo>

using namespace std;
using namespace arma;


double acceleration(double M, double pos_obj1, double pos_obj2, int beta);
double T_end = 0.001;
int N = 1000;

int main(int argc, char *argv[]) {
  Methods my_method;
  Class_name my_solver;
  my_solver.Initialize(N);
  my_solver.solve(N, T_end, my_method.ForwardEuler, acceleration);
}


double acceleration(double M, double pos_obj1, double pos_obj2, int beta){
  double ax = G*M/pow((pos1[0]-pos2[0]),beta);
  double ay = G*M/pow((pos1[1]-pos2[1]),beta);
  return ax, ay;
}
