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
void Class_name::Initialize(double vx0, double vy0, double h, double T_end, double beta){
  //2459134.500000000 = A.D. 2020-Oct-12
  m_beta = beta;
  m_h = h;
  m_N = T_end/h+1;
  double x0 = 9.384887914865430E-01;   //AU
  double y0 = 3.287443922398884E-01;   //AU
  m_vx0 = -5.838932265148174E-03 * 365.;    //AU/year
  m_vy0 = 1.621801974258600E-02 * 365.;   //AU/year
  m_x = vec(m_N, fill::zeros);
  m_y = vec(m_N, fill::zeros);

  m_x(0) = x0;
  m_y(0) = y0;
  m_x(0) = 1.;  //test case
  m_y(0) = 0.;  //test case
  m_vx0 = vx0;
  m_vy0 = vy0;   //test case
  
  }

}

void Class_name::Solve(vec chosen_method(vec pos_obj1, vec sun_pos, vec old_vel, double h, double M, double beta, vec accel_func(double M, vec pos_obj1, vec pos_obj2, double beta)), vec accel_func(double M, vec pos_obj1, vec pos_obj2, double beta)){
  double M = 1.;
  vec old_vel;
  old_vel = vec(2, fill::zeros);
  old_vel(0) = m_vx0;
  old_vel(1) = m_vy0;
  vec sun_pos;
  sun_pos = vec(2, fill::zeros);

  //int beta = 2;
  vec pos_obj1;
  pos_obj1 = vec(2, fill::zeros);
  double new_x, new_y, new_vx, new_vy;
  cout << m_beta << endl;
  for (int i = 0; i < m_N-1; i++){
    pos_obj1(0) = m_x(i);
    pos_obj1(1) = m_y(i);
    vec result = chosen_method(pos_obj1, sun_pos, old_vel, m_h, M, m_beta, accel_func);
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
