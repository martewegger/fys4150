// class file
// This is where all functions are specified.

#include "header_file.hpp"
#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <armadillo>

#define pi 3.14159265359

using namespace std;
using namespace arma;

// Function initializing variables
void Class_name::Initialize(int N){
  //2459134.500000000 = A.D. 2020-Oct-12

  double x0 = 9.384887914865430E-01;   //AU
  double y0 = 3.287443922398884E-01;   //AU
  m_vx0 = -5.838932265148174E-03 * 365.;    //AU/year
  m_vy0 = 1.621801974258600E-02 * 365.;   //AU/year
  m_N = N;
  m_x = vec(m_N, fill::zeros);
  m_y = vec(m_N, fill::zeros);

  //m_x(0) = x0;
  //m_y(0) = y0;
  m_x(0) = 1.;  //test case
  m_y(0) = 0.;  //test case
  m_vx0 = 0.;   //test case
  m_vy0 = 6.5;   //test case

}

vec Class_name::ForwardEuler(vec pos_obj1, vec pos_obj2, vec vel, double h, double M, int beta, vec accel_func(double M, vec pos_obj1, vec pos_obj2, int beta)){
  double old_vx = vel(0);
  double old_vy = vel(1);
  double old_x = pos_obj1(0);
  double old_y = pos_obj1(1);
  vec acc = accel_func(M, pos_obj1, pos_obj2, beta);
  double new_x = old_x+h*old_vx+h*h*acc(0);
  double new_vx = old_vx+h*acc(0);

  double new_y = old_y+h*old_vy + h*h*acc(1);
  double new_vy = old_vy+h*acc(1);

  vec result;
  result = vec(4, fill::zeros);
  result(0) = new_x;
  result(1) = new_y;
  result(2) = new_vx;
  result(3) = new_vy;
  return result;
}

vec Class_name::Verlet(vec pos_obj1, vec pos_obj2, vec vel, double h, double M, int beta, vec accel_func(double M, vec  pos_obj1, vec pos_obj2, int beta)){
  double old_vx = vel(0);
  double old_vy = vel(1);
  double old_x = pos_obj1(0);
  double old_y = pos_obj1(1);

  vec acc = accel_func(M, pos_obj1, pos_obj2, beta);

  double new_x = old_x + h*old_vx +  (h*h)/2 * acc(0);
  double new_y = old_y + h*old_vy +  (h*h)/2 * acc(1);
  pos_obj1[0] = new_x;
  pos_obj1[1] = new_y; //reusing pos_obj for new position

  vec new_acc = accel_func(M, pos_obj1, pos_obj2, beta);

  double new_vx = old_vx + h/2 * (new_acc(0)+acc(0));
  double new_vy = old_vy + h/2 * (new_acc(1)+acc(1));
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

void Class_name::Solve(double T_end, vec accel_func(double M, vec pos_obj1, vec pos_obj2, int beta)){
  double h = T_end/m_N;
  double M = 1.;
  vec old_vel;
  old_vel = vec(2, fill::zeros);
  old_vel(0) = m_vx0;
  old_vel(1) = m_vy0;

  vec sun_pos;
  sun_pos = vec(2, fill::zeros);

  int beta = 2;
  vec pos_obj1;
  pos_obj1 = vec(2, fill::zeros);
  double new_x, new_y, new_vx, new_vy;

  for (int i=0;i<m_N-1; i++){
    pos_obj1(0) = m_x(i);
    pos_obj1(1) = m_y(i);

    //vec result = chosen_method(pos_obj1, sun_pos, old_vel, h, M, beta, accel_func);
    vec result = Verlet(pos_obj1, sun_pos, old_vel, h, M, beta, accel_func);
    //vec result = ForwardEuler(pos_obj1, sun_pos, old_vel, h, M, beta, accel_func);

    m_x(i+1) = result(0);
    m_y(i+1) = result(1);
    old_vel(0) = result(2);
    old_vel(1) = result(3);
  }
}


// Function writing results to file
void Class_name::Write_to_file(string filename){
  ofstream ofile;
  ofile.open(filename);
  ofile << "#Tellus" << endl;
  ofile << "#X";
  ofile << "     " <<  "Y" << endl;
  for (int i = 0; i < m_N; i++){
    ofile << m_x(i);
    ofile << "     " << m_y(i) << endl;
  }
  ofile.close();
}
