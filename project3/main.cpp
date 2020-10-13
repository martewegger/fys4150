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

#define pi 3.14159265359


vec accel_func(double M, vec pos_obj1, vec pos_obj2, int beta);
vec ForwardEuler(vec pos_obj1, vec pos_obj2, vec vel, double h, double M, int beta, vec accel_func(double M, vec pos_obj1, vec pos_obj2, int beta));
double T_end = 1.1;
int N = 1e6;

int main(int argc, char *argv[]) {
  int N = atol(argv[1]);
  //string filename = "Tellus.txt";
  string filename = argv[2];
  double vy0 = atof(argv[3]);
  double h = atof(argv[4]);
  Class_name my_solver;
  my_solver.Initialize(N, vy0);
  my_solver.Solve(T_end, accel_func);
  //my_solver.Solve(T_end, my_solver.ForwardEuler, accel_func);
  my_solver.Write_to_file(filename);
}



vec accel_func(double M, vec pos_obj1, vec pos_obj2, int beta){
  double G = 4. * pi*pi;
  double x = pos_obj1(0)-pos_obj2(0);
  double y = pos_obj1(1)-pos_obj2(1);
  double r = sqrt(pow(x,2) + pow(y,2));
  double ax = -G*x / pow(r, beta+1);  //G*M / pow(pos_obj1(0)-pos_obj2(0),beta);
  double ay = -G*y / pow(r, beta+1);  //G*M / pow(pos_obj1(1)-pos_obj2(1),beta);
  vec acc;
  acc = vec(2, fill::zeros);
  acc(0) = ax;
  acc(1) = ay;
  return acc;
}

vec ForwardEuler(vec pos_obj1, vec pos_obj2, vec vel, double h, double M, int beta, vec accel_func(double M, vec pos_obj1, vec pos_obj2, int beta)){
  double old_vx = vel(0);
  double old_vy = vel(1);
  double old_x = pos_obj1(0);
  double old_y = pos_obj1(1);
  vec acc = accel_func(M, pos_obj1, pos_obj2, beta);
  double new_x = old_x + h*old_vx + h*h*acc(0);
  double new_vx = old_vx + h*acc(0);

  double new_y = old_y + h*old_vy + h*h*acc(1);
  double new_vy = old_vy + h*acc(1);

  vec result;
  result = vec(4, fill::zeros);
  result(0) = new_x;
  result(1) = new_y;
  result(2) = new_vx;
  result(3) = new_vy;
  return result;
}
