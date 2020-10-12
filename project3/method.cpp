// class file
// This is where all functions are specified.

#include "header_file.hpp"
#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <armadillo>
#define pi 3.14159265359
#define G = 4 * pi*pi


using namespace std;
using namespace arma;

// Function initializing variables
double Methods::ForwardEuler(double pos_obj1, double pos_obj2, double vel, double h, double acceleration(double M, double  pos_obj1, double pos_obj2, int beta)){
  old_vx, old_vy = vel;
  old_x, old_y = pos_obj1;

  ax, ay = acceleration(M, pos_obj1, pos_obj2);
  double new_x = old_x+h*old_vx;
  double new_vx = old_vx+h*ax;

  double new_y = old_y+h*old_vy;
  double new_vy = old_vy+h*ay;

  return [new_x, new_y], [new_vx, new_vy];
}

double Methods::Verlet(double pos_obj1, double pos_obj2, double vel, double h, double acceleration(double M, double  pos_obj1, double pos_obj2, int beta)){
  old_vx, old_vy = vel;
  old_x, old_y = pos_obj1;
  old_ax, old_ay = acceleration(M, pos_obj1, pos_obj2);

  double new_x = old_x + h*old_vx +  h/2*old_ax;
  double new_y = old_y + h*old_vy +  h/2*old_ay;

  new_ax, new_ay = acceleration(M, [new_x,new_y], pos_obj2);

  double new_vx = old_vx + h/2*(new_ax+old_ax);
  double new_vy = old_vy + h/2*(new_ay+old_ay);

  return [new_x, new_y], [new_vx, new_vy];
}
