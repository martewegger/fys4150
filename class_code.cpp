// class file
// This is where all functions are specified.

#include "header_file.hpp"
#include <iostream>
#include <cmath>
#include <fstream> //til plottegreiene
#include <string>

using namespace std;

void Classname::Initialize(int n){

  x0 = 0.;            // enten . eller "double" foran for å si at det er en float
  xn = 1.;
  m_n = n;            //steplength ligger i mainfile
  h = (xn - x0)/(m_n+2);

  // General case
  a = new double[m_n]; //allokere minne
  b = new double[m_n];
  c = new double[m_n];
  q = new double[m_n];
  p = new double[m_n];
  b_tilde = new double[m_n];
  m_v = new double[m_n];
  m_x_gen = new double[m_n];
  v_analytic = new double[m_n];

  // Special case
  di = -2.;
  ei = 1.;
  m_u = new double[m_n]; //allokere minne
  m_x_spec = new double[m_n]; //deklarerer array x med lengde m_n
  g_tilde = new double[m_n];
  d_tilde = new double[m_n];
  u_analytic = new double[m_n];
  d_tilde[0] = di;

}



// General:
void Classname::Function_general(double f(double xi), double u_func(double xi)){

  q[0] = pow(h,2)*f(x0); //fordi q1 = btilde1

  for(int i = 1; i < m_n; i++){ //Forward part
    m_x_gen[i] = x0 + (i+1)*h;
    bi_tilde = pow(h,2) * f(m_x_gen[i]);
    q[i] = bi_tilde - ((b_tilde[i-1]*a[i-1]) / b[i-1]);
    p[i] = b[i] - ((b_tilde[i-1]*a[i-1])/b[i-1]);
    v_analytic[i] = u_func(m_x_gen[i]);
  }

  m_v[m_n-1] =  q[m_n-1]/p[m_n-1];
  for (int i = (m_n-2); i >= 0; i--){ //Backward part
    m_v[i] = (b_tilde[i]-(c[i]*m_v[i+1]))/p[i];
  }

}

// Special:
void Classname::Function_special(double f(double xi), double u_func(double xi)){


  g_tilde[0] = pow(h,2)*f(h); //må ha denne her fordi vi bruker f, why h, skal være x0??

  for(int i = 1; i < m_n; i++){ //Forward part
    m_x_spec[i] = x0 + (i+1)*h;
    gi = pow(h,2) * f(m_x_spec[i]);
    g_tilde[i] = gi - (g_tilde[i-1] / d_tilde[i-1]);
    d_tilde[i] = - (double) (i+1)/i; //den gjorde heltallsdivisjon, den trunkerte
    u_analytic[i] = u_func(m_x_spec[i]);
  }

  m_u[m_n-1] =  g_tilde[m_n-1]/d_tilde[m_n-1];
  for (int i = (m_n-2); i >= 0; i--){ //Backward part
    m_u[i] = (g_tilde[i] - m_u[i+1])/d_tilde[i];
  }

}


void Classname::Write_to_file(string filename){

    m_ofile.open(filename);
    m_ofile <<'#'<< 'x' <<  "               " << "numerical u" << "     "<< "analytic u" << endl;
    m_ofile << m_x_spec[0] <<  "               " << m_u[0] << "            "<< u_analytic[0] << endl;
    for (int i = 1; i < m_n; i++){

      m_ofile << m_x_spec[i] <<  "       " << m_u[i] << "       "<< u_analytic[i] << endl;
    }
    m_ofile.close();

}
