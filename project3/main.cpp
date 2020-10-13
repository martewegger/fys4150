// main file
// The main program is where you use the actual class.

#include "header_file.hpp"
//#include "method.cpp"
#include <iostream>
#include <cmath>
#include <string>
#include <ctime>
#include <armadillo>

using namespace std;
using namespace arma;

#define pi 3.14159265359
#define G 4. * pi*pi


vec acceleration(double M, vec pos_obj1, vec pos_obj2, int beta);
double T_end = 0.001;
int N = 1000;

int main(int argc, char *argv[]) {
  Class_name my_solver;
  my_solver.Initialize(N);
  my_solver.solve(T_end, my_solver.ForwardEuler, acceleration);
}


vec acceleration(double M, vec pos_obj1, vec pos_obj2, int beta){
  double ax = G*M/pow((pos_obj1(0)-pos_obj2(0),beta);
  double ay = G*M/pow((pos1[1]-pos2[1]),beta);
  vec acc;
  acc = vec(2, fill::zeros);
  acc(0) = ax;
  acc(1) = ay;
  return acc;
}
