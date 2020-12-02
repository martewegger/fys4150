// main file
// The main program is where you use the actual class.

#include "PDE_2D.hpp"
#include <iostream>
#include <cmath>
//#include <string>
#include <ctime>
#define pi 3.14159265359
//#include <fstream>

//using namespace std;
double initial(double x, double y);


int main(int argc, char *argv[]){
  double T_end = atof(argv[1]);
  double dt  = atof(argv[2]);
  double dxy  = atof(argv[3]);
  string method = argv[4];

  PDE_2D my_instance;
  my_instance.Initialise(T_end, dt, dxy, initial); //kan ha mange ulike initializere.
  if (method=="ForwardEuler"){
    //double a = 1.;
    my_instance.ForwardEuler();
  }
  return 0;
}

double initial(double x, double y){
  return sin(pi*x)*sin(pi*y);
}
