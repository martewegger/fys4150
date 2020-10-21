// class file
// This is where all functions are specified.

#include "header_file.hpp"
#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <armadillo>

#define pi 3.14159265359
#define M_sun 1.9891E30 // 1 solar mass in kg

using namespace std;
using namespace arma;

// Function initializing variables
void Class_name::Initialize(double h, double T_end, string filename, double beta){

  //2459134.500000000 = A.D. 2020-Oct-12 00:00:00.0000 TDB
  m_filename = filename;
  m_Nbody = 3;
  m_beta = beta;
  cout << "beta = "<<m_beta<<endl;
  cout << "dt = " << h<< endl;
  m_N = T_end/h+1;
  cout << "N = "<<m_N<<endl;
  m_h = h;
  m_G = 4. * pi*pi;

  double x0_earth = 9.384887914865430E-01;   //AU
  double y0_earth = 3.287443922398884E-01;   //AU
  double vx0_earth = -5.838932265148174E-03 *365.;    //AU/year
  double vy0_earth = 1.621801974258600E-02 *365.;   //AU/year

  m_x_old = vec(m_Nbody, fill::zeros);
  m_y_old = vec(m_Nbody, fill::zeros);
  m_vx_old = vec(m_Nbody, fill::zeros);
  m_vy_old = vec(m_Nbody, fill::zeros);
  m_vx_new = vec(m_Nbody, fill::zeros);
  m_vy_new = vec(m_Nbody, fill::zeros);

  m_x_new = vec(m_Nbody, fill::zeros);
  m_y_new = vec(m_Nbody, fill::zeros);

  m_acc = vec(2, fill::zeros);

  m_mass = vec(m_Nbody, fill::zeros);

  m_mass(0) = 1.; //Solar mass
  m_mass(1) = 0.;//5.972E24/M_sun;
  m_mass(2) = 0.*1.898E27/M_sun;
  //cout << "Jupiter mass = " << m_mass(2) << endl;
  m_x_old(1) = 1.;//x0_earth;
  m_y_old(1) = 0.;//y0_earth;

  m_x_old(0) = 0.;//-6.078749760969366E-03;
  m_y_old(0) = 0.;//6.440972971387628E-03;

  m_x_old(2) = 5.;//2.530840380497989E+00;
  m_y_old(2) = 0.;//-4.445040606335634E+00;

  m_vx_old(2) = 0.;//6.464708585362312E-03* 365.; //Jupiter
  m_vy_old(2) =2*pi/sqrt(5);//4.091363589634699E-03* 365.;

  m_vx_old(1) =0.;// vx0_earth;
  m_vy_old(1) =2.*pi;//vy0_earth;
  m_vx_old(0) = 0.;//-7.307311063335453E-06* 365.; // Sun
  m_vy_old(0) = 0.;//-5.056308815628042E-06* 365.; // Sun

  //m_vx(2) = 0.;
  //m_vy(2) = 0.;
  //m_mass(2) = 0.;


  m_vx_old(0) = -1./m_mass(0)*(m_mass(1)*m_vx_old(1)+m_mass(2)*m_vx_old(2));
  m_vy_old(0) = -1./m_mass(0)*(m_mass(1)*m_vy_old(1)+m_mass(2)*m_vy_old(2));

  m_ofile.open(filename);
  m_ofile << setw(30) << "#Sun";
  m_ofile << setw(30) <<"Earth";
  m_ofile << setw(30)<< "Jupiter" << endl;
  m_ofile << "#";
  for (int i=0;i<m_Nbody;i++){
    m_ofile << setw(15)<< "X";
    m_ofile << setw(15)<< "Y";
  }
  m_ofile << endl;
  for (int j=0;j<m_Nbody;j++){
    m_ofile << setw(15)<< m_x_old(j);
    m_ofile <<setw(15)<< m_y_old(j);
  }
  m_ofile << endl;
}

void Class_name::Write_to_file(){
  for (int i = 0; i < m_Nbody; i++){
    m_ofile << setw(15)<< m_x_new(i);
    m_ofile << setw(15)<< m_y_new(i);
  }
  m_ofile << endl;
}

void Class_name::diff_eq(int i, int j){
  double x = m_x_old(i)-m_x_old(j);
  double y = m_y_old(i)-m_y_old(j);
  double r = sqrt(pow(x,2) + pow(y,2));
  double ax = -m_G*x*m_mass(j) / pow(r, m_beta+1);
  double ay = -m_G*y*m_mass(j) / pow(r, m_beta+1);
  m_acc(0) = ax;
  m_acc(1) = ay;
}



void Class_name::Verlet(){
  vec new_acc, old_acc;
  for (int i = 0; i < m_Nbody; i++){
    old_acc = vec(2, fill::zeros);
    new_acc = vec(2, fill::zeros);
    for (int j = 0; j < m_Nbody; j++){
      if (i != j){
        diff_eq(i, j);
        //cout<<"acceleration"<< "i,j="<<i<<j<< m_acc<<endl;
        old_acc += m_acc;
        //cout << "old_acc"<< old_acc << endl;
      }
    }
    //cout << "indx= "<< i<<endl;
    //cout << "old_acc"<< old_acc << endl;
    //cout << "m_x_new"<< m_x_new(i) << endl;

    m_x_new(i) = m_x_old(i) + m_h*m_vx_old(i) +  (m_h*m_h)/2 * old_acc(0);
    //cout << "old_acc"<< old_acc << endl;
    //cout << "m_x_new"<< m_x_new(i) << endl;
    m_y_new(i) = m_y_old(i) + m_h*m_vy_old(i) +  (m_h*m_h)/2 * old_acc(1);
    for (int k=0;k<m_Nbody;k++){
      if(i != k){
        diff_eq(i, k);
        new_acc+= m_acc;
      }
    }
    m_vx_new(i) = m_vx_old(i) + m_h/2 * (new_acc(0)+old_acc(0));
    m_vy_new(i) = m_vy_old(i) + m_h/2 * (new_acc(1)+old_acc(1));
    m_vx_old(i) = m_vx_new(i);
    m_vy_old(i) = m_vy_new(i);
  }
  m_x_old = m_x_new;
  m_y_old = m_y_new;
}


void Class_name::Solve(){
  for (int i = 0; i < m_N-1; i++){
    Verlet();
    Write_to_file();
  }
  m_ofile.close();
}
