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
double v_func(double xi);



int main(int argc, char const *argv[]) {
  //Parameters
  int n = 1000;
  int cond=100000;
  string filename = "data.txt";
  //string filename = "data_1000.txt";


  Class_Poisson_Dirichlet my_solver; //initiate class

  my_solver.Initialize(n, cond);    // call function for parameter initiation

  clock_t c_start_gen = clock(); // timing the following function
  my_solver.Function_general(f,v_func);   // solving the diff. eq. with the general algorithm
  clock_t c_end_gen = clock();

  clock_t c_start_spec = clock();
  my_solver.Function_special(f,v_func); // call to the special algorithm
  clock_t c_end_spec = clock();

  my_solver.print_relative_error(v_func);   // a function for printing log10(max relative errors) to terminal

  clock_t c_start_lu = clock();
  if (n<cond){ // if statement to only run LU algo if N<1e5
    my_solver.lu_decomp(f); // LU decomposition algorithm
  }
  clock_t c_end_lu = clock();

  if (n<cond){
    my_solver.Write_to_file(filename); // function that writes data to file
  }

  long double time_elapsed_ms_gen = 1000.0 * (c_end_gen-c_start_gen) / CLOCKS_PER_SEC;
  cout << "CPU time used for general algo: " << time_elapsed_ms_gen << " ms" << endl;
  long double time_elapsed_ms_spec = 1000.0 * (c_end_spec-c_start_spec) / CLOCKS_PER_SEC;
  cout << "CPU time used for special algo: " << time_elapsed_ms_spec << " ms" << endl;

  long double time_elapsed_ms_lu = 1000.0 * (c_end_lu-c_start_lu) / CLOCKS_PER_SEC;
  cout << "CPU time used for LU decomp: " << time_elapsed_ms_lu << " ms" << endl;

  return 0;
}
// right hand side of the differential equation
double f(double xi){
  return -100*exp(-10*xi);
}

//analytical solution to the differential equation
double v_func(double xi){
  return 1. - ((1-exp(-10))*xi) - exp(-10*xi);
}
