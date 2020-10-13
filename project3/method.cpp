// class file
// This is where all functions are specified.

#include "header_file.hpp"
#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <armadillo>
#define pi 3.14159265359
#define G 4. * pi*pi


using namespace std;
using namespace arma;

// Function initializing variables
vec Methods::ForwardEuler(vec pos_obj1, vec pos_obj2, vec vel, double h, double M, int beta, double acceleration(double M, double  pos_obj1, double pos_obj2, int beta)){
  double old_vx = vel(0);
  double old_vy = vel(1);
  double old_x, old_y = pos_obj1;
  double ax, ay = acceleration(M, pos_obj1, pos_obj2, beta);
  double new_x = old_x+h*old_vx+h*h*ax;
  double new_vx = old_vx+h*ax;

  double new_y = old_y+h*old_vy + h*h*ay;
  double new_vy = old_vy+h*ay;

  vec result;
  result = vec(4, fill::zeros);
  result(0) = new_x;
  result(1) = new_y;
  result(2) = new_vx;
  result(3) = new_vy;
  return result;
}

vec Methods::Verlet(double pos_obj1, double pos_obj2, double vel, double h, double M, int beta, double acceleration(double M, double  pos_obj1, double pos_obj2, int beta)){
  double old_vx, old_vy = vel;
  double old_x, old_y = pos_obj1;
  double old_ax, old_ay = acceleration(M, pos_obj1, pos_obj2, beta);

  double new_x = old_x + h*old_vx +  h/2*old_ax;
  double new_y = old_y + h*old_vy +  h/2*old_ay;
  pos_obj1[0] = new_x;
  pos_obj1[1] = new_y; //reusing pos_obj for new position
  double new_ax, new_ay = acceleration(M, pos_obj1, pos_obj2);

  double new_vx = old_vx + h/2*(new_ax+old_ax);
  double new_vy = old_vy + h/2*(new_ay+old_ay);
  //double *result;
  //result = new double[4];
  vec result;
  result = vec(4, fill::zeros);
  result(0) = new_x;
  result(1) = new_y;
  result(2) = new_vx;
  result(3) = new_vy;
  return result;
}



class Methods {
private:
  double test;
public:
  vec ForwardEuler(vec pos_obj1, vec pos_obj2, vec vel, double h, double M, int beta, vec acceleration(double M, vec  pos_obj1, vec pos_obj2, int beta));
  vec Verlet(vec pos_obj1, vec pos_obj2, vec vel, double h, double M, int beta, vec acceleration(double M, vec  pos_obj1, vec pos_obj2, int beta));
};
