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




int main(int argc, char const *argv[]) {
  //Parameters
  int n = 10;
  int cond=100000;
  string filename = "data.txt";
  //string filename = "data_1000.txt";


  Class_name my_solver; //initiate class
  my_solver.Initialize(n);
  my_solver.Solver();
  my_solver.Eigenstuff_func();
  my_solver.Write_to_file(filename);


  return 0;
}
