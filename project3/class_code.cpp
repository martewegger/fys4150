// class file
// This is where all functions are specified.

#include "header_file.hpp"
#include "method.cpp"
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
  m_vx0=-5.838932265148174E-0;    //AU/day
  m_vy0= 1.621801974258600E-02;   //AU/day
  m_N = N;
  m_x = vec(m_N, fill::zeros);
  m_y = vec(m_N, fill::zeros);

  m_x(0) = x0;
  m_y(0) = y0;
  m_x(0) = 1.;  //test case
  m_y(0) = 0.;  // test case
}


void Class_name::solve(double T_end, double method, double accel_func){
  double h = T_end/m_N;
  double M_solar = 1.;

  vec old_vel;
  result = vec(2, fill::zeros);
  old_vel(0) = m_vx0;
  old_vel(1) = m_vy0;

  vec sun_pos;
  sun_pos = vec(2, fill:zeros);

  int beta = 2;
  vec pos_obj1;
  pos_obj1 = vec(2, fill::zeros);

  for (i=0;i<m_N-1; i++){
    pos_obj1(0) = m_x(i);
    pos_obj1(1) = m_y(i);

    double new_x, new_y, new_vx, new_vy = method(pos_obj1, sun_pos, old_vel, h, M_solar, beta, accel_func);
    m_x(i+1) = new_x;
    m_y(i+1) = new_y;
    old_vel(0) = new_vx;
    old_vel(1) = new_vy;
    cout << new_pos << endl;
  }
}

// Function writing results to file
void Class_name::Write_to_file(string filename){
  m_ofile.open(filename);
  m_ofile << setw(15) << " # Eigenvalue";
  m_ofile << setw(15) << " A_ii"<<endl;
  for (int i = 0; i< m_n; i++){
    m_ofile << setw(15) << setprecision(8) << m_eigvals[i];
    m_ofile << setw(15) << setprecision(8) << m_A(i,i)<<endl;
  }
  m_ofile.close();
}
