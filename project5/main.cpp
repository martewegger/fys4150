// main file
// The main program is where you use the actual class.

#include "PDE.hpp"
#include <iostream>
#include <cmath>
//#include <string>
#include <ctime>
//#include <fstream>

//using namespace std;

int main(int argc, char *argv[]){
  double T_end = atof(argv[1]);
  double dt  = atof(argv[2]);
  double dx  = atof(argv[3]);
  string method = argv[4];

  PDE my_instance;
  my_instance.Initialise(T_end, dt, dx); //kan ha mange ulike initializere.
  if (method=="ForwardEuler"){
    //double a = 1.;
    my_instance.ForwardEuler();
  }

  if (method=="Crank_Nicolsen"){
    //double a = 1.;
    my_instance.Crank_Nicolsen();
    }
  return 0;
}
