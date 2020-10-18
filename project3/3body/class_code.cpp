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
void Class_name::Initialize(double vx0, double vy0, double h, double T_end, string filename){

  //2459134.500000000 = A.D. 2020-Oct-12
  m_filename = filename;
  m_Nbody = 3;
  m_N = T_end/h+1;
  m_h = h;
  m_N = T_end/h+1;
  double x0_earth = 9.384887914865430E-01;   //AU
  double y0_earth = 3.287443922398884E-01;   //AU
  vx0_earth = -5.838932265148174E-03 *365.;    //AU/year
  vy0_earth = 1.621801974258600E-02 *365.;   //AU/year
  m_x_old = vec(m_Nbody, fill::zeros);
  m_y_old = vec(m_Nbody, fill::zeros);
  m_vx_old = vec(m_Nbody, fill::zeros);
  m_vy_old = vec(m_Nbody, fill::zeros);

  m_x_new = vec(m_Nbody, fill::zeros);
  m_y_new = vec(m_Nbody, fill::zeros);
  m_vx_new = vec(m_Nbody, fill::zeros);
  m_vy_new = vec(m_Nbody, fill::zeros);

  m_mass = vec(m_Nbody, fill::zeros);

  m_x_old(1) = x0_earth;
  m_y_old(1) = y0_earth;

  m_x_old(0) = -6.122473398487174E-03;
  m_y_old(0) = 6.410482460526987E-03;

  m_x_old(2) = 2.569528464099691E+00;
  m_y_old(2) = -4.420315510127981E+00;

  m_vx_old(1) = vx0_earth;
  m_vy_old(1) = vy0_earth;

  m_vx_old(0) = -7.267300123827440E-06* 365.; // Sun
  m_vy_old(0) = -5.107009024048823E-06* 365.; // Sun

  m_vx_old(2) = 6.432012793032114E-03* 365.; //Jupiter
  m_vy_old(2) = 4.150995088200494E-03* 365.;


  m_ofile.open(filename);
  m_ofile << setw(30) << "#Sun" <<;
  m_ofile << setw(30) <<"Earth" <<;
  m_ofile << setw(30)<< "Jupiter" << endl;
  m_ofile << "#" <<;
  for (int i=0;i<m_Nbody;i++){
    m_ofile << setw(15)<< "X" <<;
    m_ofile << setw(15)<< "Y" <<;
  }
  m_ofile << endl;
  for (int j=0;j<m_Nbody;j++){
    m_ofile << setw(15)<< m_x_old(j)<<;
    m_ofile <<setw(15)<< m_y_old(j) <<;
  }
  m_ofile << endl;
}

void Class_name::Write_to_file(){

  for (int i = 0;i<m_Nbody;i++){
    m_ofile << setw(15)<< m_x_new(i) <<;
    m_ofile << setw(15)<< m_y_new(i) <<;
  }
  m_ofile << endl;
}

void diff_eq(){
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
}



void Class_name::Verlet(){
  vec new_acc[2];
  vec old_acc[2];
  for (int i=0;i<m_Nbody;i++){
    old_acc = vec(fill::zeros);
    new_acc = vec(fill::zeros);
    for (int j = 0;j<m_Nbody;j++){
      if (i!=j){
        old_acc += diff_eq(M, pos_obj1, pos_obj2, beta);
      }
    }
    m_x_new(i) = m_x_old(i) + h*m_vx_old(i) +  (h*h)/2 * old_acc(0);
    m_y_new(i) = m_y_old(i) + h*m_vy_old(i) +  (h*h)/2 * old_acc();
    for (int k=0;k<m_Nbody;k++){
      if(k!=i){


      }
    }
        vec new_acc = diff_eq(M, pos_obj1, pos_obj2, beta);

        double new_vx = old_vx + h/2 * (new_acc(0)+acc(0));
        double new_vy = old_vy + h/2 * (new_acc(1)+acc(1));
      }

    }
  }
  Write_to_file();

}

void Class_name::Solve(){

  for (int i = 0; i < m_N-1; i++){
    Verlet();
  }
  m_ofile.close();
}




// Function writing results to file
