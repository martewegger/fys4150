// main file
// The main program is where you use the actual class.

#include "header_file.hpp"
#include <iostream>
#include <cmath>
#include <string>
#include <ctime>

using namespace std;

double f(double xi);
double u_func(double xi);



int main(int argc, char const *argv[]) {
  //Parameters
  int n = 1000000;
  string filename = "data_10.txt";

  //Solve integral
  Classname my_solver;
  my_solver.Initialize(n);
  clock_t c_start_gen = clock();
  //my_solver.Function_general(f,u_func);
  clock_t c_end_gen = clock();
  clock_t c_start_spec = clock();
  my_solver.Function_special(f,u_func);
  clock_t c_end_spec = clock();
  //my_solver.Write_to_file(filename);
  my_solver.print_relative_error();

  long double time_elapsed_ms_gen = 1000.0 * (c_end_gen-c_start_gen) / CLOCKS_PER_SEC;
  cout << "CPU time used for general algo: " << time_elapsed_ms_gen << " ms" << endl;
  long double time_elapsed_ms_spec = 1000.0 * (c_end_spec-c_start_spec) / CLOCKS_PER_SEC;
  cout << "CPU time used for special algo: " << time_elapsed_ms_spec << " ms" << endl;

  return 0;
}

double f(double xi){
  return -100*exp(-10*xi);
}

double u_func(double xi){
  return 1 - ((1-exp(-10))*xi) - exp(-10*xi);
}
