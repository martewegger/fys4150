// main file
// The main program is where you use the actual class.

#include "header_file.hpp"
#include <iostream>
#include <cmath>

using namespace std;

double f(double xi);
double u_func(double xi);

int main(int argc, char const *argv[]) {
  //Parameters
  int n = 10;

  //Solve integral
  Classname my_solver;
  my_solver.Initialize(n);
  my_solver.Function(f,u_func);
  //my_solver.Print(); //ha den imens, kanskje fjerne?

  return 0;
}

double f(double xi){
  return -100*exp(-10*xi);
}

double u_func(double xi){
  return 1 - ((1-exp(-10))*xi) - exp(-10*xi);
}
