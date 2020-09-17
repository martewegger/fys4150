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

double f(double xi);



int main(int argc, char const *argv[]) {
  //Parameters
  int n = 1000;
  int cond=100000;
  string filename = "data.txt";
  //string filename = "data_1000.txt";


  Class_Poisson_Dirichlet my_solver; //initiate class


  return 0;
}
