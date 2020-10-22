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
  m_Nbody = 9;
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

  m_x = vec(m_Nbody, fill::zeros);
  m_y = vec(m_Nbody, fill::zeros);
  m_vx_old = vec(m_Nbody, fill::zeros);
  m_vy_old = vec(m_Nbody, fill::zeros);
  m_vx_new = vec(m_Nbody, fill::zeros);
  m_vy_new = vec(m_Nbody, fill::zeros);

  m_acc = vec(2, fill::zeros);

  m_mass = vec(m_Nbody, fill::zeros);

  m_mass(0) = 1.; //Solar mass
  //m_mass(1) = 3.3E23/M_sun;
  m_mass(1) = 4.9E24/M_sun;
  m_mass(2) = 5.972E24/M_sun;
  m_mass(3) = 6.6E23/M_sun;
  m_mass(4) = 1.898E27/M_sun;
  m_mass(5) = 5.5E26/M_sun;
  m_mass(6) = 8.8E25/M_sun;
  m_mass(7) = 1.E26/M_sun;
  m_mass(8) = 1.3E22/M_sun;

  //cout << "Jupiter mass = " << m_mass(2) << endl;

  m_x(0) = -6.122473398487174E-3;
  m_y(0) = 6.410482460526987E-3;

  m_x(1) = -2.593074555306261E-1;
  m_y(1) = 6.786561172635504E-1;

  m_x(2) = 8.984239561537140E-1;
  m_y(2) = 4.241593607051067E-1;

  m_x(3) = 1.298826322121149;
  m_y(3) = 5.662069485224839E-1;

  m_x(4) = 2.569528464099691;
  m_y(4) = -4.420315510127981;

  m_x(5) = 5.152970564937138;
  m_y(5) = -8.557980521297571;

  m_x(6) = 1.552991486743390E1;
  m_y(6) =1.225108114470249E1;

  m_x(7) = 2.941338926533959E1;
  m_y(7) = -5.458868379880593;

  m_x(8) =1.383356606211680E1;
  m_y(8) = -3.119798652278261E1;

  m_vx_old(1) =-1.900391839216583E-2* 365;
  m_vy_old(1) = -7.247860847576755E-3* 365;

  m_vx_old(2) = -7.505790752250796E-3* 365;
  m_vy_old(2) = 1.555524120490925E-2* 365;

  m_vx_old(3) = -4.988664931466998E-3* 365;
  m_vy_old(3) = 1.404997171659795E-2* 365;

  m_vx_old(4) = 6.432012793032114E-3* 365;
  m_vy_old(4) = 4.150995088200494E-3* 365;

  m_vx_old(5) = 4.467883275314033E-3* 365;
  m_vy_old(5) = 2.863553376831038E-3* 365;

  m_vx_old(6) = -2.465040979168495E-3* 365;
  m_vy_old(6) = 2.904702477181378E-3* 365;

  m_vx_old(7) = 5.522227196905099E-4* 365;
  m_vy_old(7) = 3.105503404723992E-3* 365;

  m_vx_old(8) = 2.942753009796773E-3* 365;
  m_vy_old(8) = 5.927341579097886E-4* 365;

  //m_Nbody = 5;
  for (int i = 1;i<m_Nbody;i++){
    m_vx_old(0) -= m_mass(i)*m_vx_old(i);
    m_vy_old(0) -= m_mass(i)*m_vy_old(i);
  }
  m_Nbody = 3;
  if (m_Nbody==3){
    m_x = vec(m_Nbody, fill::zeros);
    m_y = vec(m_Nbody, fill::zeros);
    m_vx_old = vec(m_Nbody, fill::zeros);
    m_vy_old = vec(m_Nbody, fill::zeros);
    m_vx_new = vec(m_Nbody, fill::zeros);
    m_vy_new = vec(m_Nbody, fill::zeros);
    m_acc = vec(2, fill::zeros);
    m_mass = vec(m_Nbody, fill::zeros);
    m_x(0)=0.;
    m_y(0) = 0.;
    m_x(1) =1.;
    m_y(1) = 0.;
    m_x(2) = 5.;
    m_y(2) = 0;
    m_vx_old(0) = 0.;
    m_vy_old(0) = 0.;
    m_vx_old(1) = 0.;
    m_vy_old(1) = 2*pi;
    m_vx_old(2) = 0.;
    m_vy_old(2) = (pi*pi)/4;
    m_mass(0) = 1.;
    m_mass(1) = 1.*5.972E24/M_sun;
    m_mass(2) = 1.*1.898E27/M_sun;
    for (int i = 1;i<m_Nbody;i++){
      m_vx_old(0) -= m_mass(i)*m_vx_old(i);
      m_vy_old(0) -= m_mass(i)*m_vy_old(i);
    }
  }
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
    m_ofile << setw(15)<< m_x(j);
    m_ofile <<setw(15)<< m_y(j);
  }
  m_ofile << endl;
}

void Class_name::Write_to_file(){
  for (int i = 0; i < m_Nbody; i++){
    m_ofile << setw(15)<< m_x(i);
    m_ofile << setw(15)<< m_y(i);
  }
  m_ofile << endl;
}

void Class_name::diff_eq(int i, int j){
  //cout<<"acceleration"<< "i,j = "<<i<<j<<endl;;//<< m_acc<<endl;
  m_acc.fill(0.);
  double x = m_x(i)-m_x(j);
  double y = m_y(i)-m_y(j);
  double r = sqrt(pow(x,2) + pow(y,2));
  m_acc(0) = -m_G*x*m_mass(j) / pow(r, m_beta+1);
  m_acc(1) = -m_G*y*m_mass(j) / pow(r, m_beta+1);
}



void Class_name::Verlet(){
  vec new_acc, old_acc;
  for (int i = 0; i < m_Nbody; i++){
    old_acc = vec(2, fill::zeros);
    new_acc = vec(2, fill::zeros);
    for (int j = 0; j < m_Nbody; j++){
      if (i != j){
        diff_eq(i, j);
        old_acc(0)+= m_acc(0);
        old_acc(1)+= m_acc(1);
      }
    }
    m_x(i) += m_h*m_vx_old(i) +  (m_h*m_h)/2 * old_acc(0);
    m_y(i) += m_h*m_vy_old(i) +  (m_h*m_h)/2 * old_acc(1);
    for (int k=0;k<m_Nbody;k++){
      if(i != k){
        diff_eq(i, k);
        new_acc(0)+=m_acc(0);
        new_acc(1)+=m_acc(1);
      }
    }
    m_vx_new(i) = m_vx_old(i) + m_h/2 * (new_acc(0)+old_acc(0));
    m_vy_new(i) = m_vy_old(i) + m_h/2 * (new_acc(1)+old_acc(1));
    m_vx_old(i) = m_vx_new(i);
    m_vy_old(i) = m_vy_new(i);
  }
}
void Class_name::Solve(){
  for (int i = 0; i < m_N-1; i++){
    Verlet();
    Write_to_file();
  }
  m_ofile.close();
}
