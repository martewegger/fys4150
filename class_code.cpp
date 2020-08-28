// class file
// This is where all functions are specified.

#include "header_file.hpp"
#include <iostream>
#include <cmath>
#include <fstream> //til plottegreiene
#include <string>

using namespace std;

void Classname::Initialize(int n){
  di = -2.;
  ei = 1.;
  x0 = 0.;            // enten . eller "double" foran for å si at det er en float
  xn = 1.;
  m_n = n;            //steplength ligger i mainfile
  h = (xn - x0)/(m_n+2);


  m_u = new double[m_n]; //allokere minne
  m_x = new double[m_n]; //deklarerer array x med lengde m_n
  g_tilde = new double[m_n];
  d_tilde = new double[m_n];
  u_analytic = new double[m_n];
  //m_x[m_n-1]=xn;

  d_tilde[0] = di;

}


void Classname::Function(double f(double xi), double u_func(double xi)){


  g_tilde[0] = pow(h,2)*f(h); //må ha denne her fordi vi bruker f

  for(int i = 1; i < m_n; i++){ //Forward part
    m_x[i] = x0 + (i+1)*h;
    gi = pow(h,2) * f(m_x[i]);
    g_tilde[i] = gi - (g_tilde[i-1] / d_tilde[i-1]);
    d_tilde[i] = - (double) (i+1)/i; //den gjorde heltallsdivisjon, den trunkerte
    u_analytic[i] = u_func(m_x[i]);
  }

  m_u[m_n-1] =  g_tilde[m_n-1]/d_tilde[m_n-1];
  for (int i = (m_n-2); i >= 0; i--){ //Backward part
    m_u[i] = (g_tilde[i] - m_u[i+1])/d_tilde[i];
  }

  //for(int i = 0; i < m_n ; i++){ //printing
    //cout << "ui = " << (u[i]) << endl;
  //}


}


void Classname::Write_to_file(string filename){

    m_ofile.open(filename);
    for (int i = 0; i < m_n; i++){
      m_ofile << m_x[i] <<  "     " << m_u[i] << endl;
    }
    m_ofile.close();

}
