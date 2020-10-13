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

  m_x0 = 9.384887914865430E-01;   //AU
  m_y0 = 3.287443922398884E-01;   //AU
  double vx0=-5.838932265148174E-0;    //AU/day
  double vy0= 1.621801974258600E-02;   //AU/day
  m_N = N;
  m_x = new double[m_N];
  m_y = new double[m_N];


  m_x[0] = m_x0;
  m_y[0] = m_y0;
  m_x[0] = 1.;
  m_y[0] = 0.;
}



void Class_name::solve(int N, double T_end, double method, double accel_func){
  double h = T_end/N;
  double M_solar = 1.;
  double old_vel = [m_vx0, m_vy0];
  double sun_pos = [0,0];
  int beta = 2;
  for (i=0;i<m_N-1; i++){
    double pos_obj1 = [m_x[i], m_y[i]];
    double new_pos, new_vel = method(pos_obj1, sun_pos, old_vel, h, M_solar, beta, accel_func);
    m_x[i+1] = new_pos[0];
    m_y[i+1] = new_pos[1];
    old_vel = new_vel;
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
