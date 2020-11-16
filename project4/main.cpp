// main file
// The main program is where you use the actual class.

#include "Ising2D.hpp"
#include <iostream>
#include <cmath>
//#include <string>
#include <ctime>
//#include <fstream>

//using namespace std;



int main(int argc, char *argv[]) {
  double T = atof(argv[1]);
  int len = atol(argv[2]);
  //string initial_state = "random";
  //string initial_state="ordered";
  string initial_state = argv[3]
  int MC = atol[];


  double T = 1.; //bare random nå
  int dim = 20; //dette er L, altså dimensjonen på matrisa
  //kalle på den initializeren:
  Ising2D my_solver(T, dim, initial_state); //kan ha mange ulike initializere.
  //my_solver.Write_to_file(); //kaller på den
  //my_solver.Metropolis_algo(dim,dim);


  int n = 0;
  my_solver.Monte_Carlo(MC, n);
  return 0;
}
