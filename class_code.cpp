// class file
// This is where all functions are specified.

#include "header_file.hpp"
#include <iostream>
#include <cmath>

using namespace std;

void Classname::Initialize(int n){
  di = -2.;
  ei = 1.;
  x0 = 0.;            // enten . eller "double" foran for å si at det er en float
  xn = 1.;
  m_n = n;            //steplength ligger i mainfile
  h = (xn - x0)/m_n;

}


void Classname::Function(double f(double xi), double u_func(double xi)){

  double g_tilde[m_n];
  double d_tilde[m_n];
  double u[m_n];      //deklarerer array u med lengde m_n
  double u_analytic[m_n];
  d_tilde[0] = di;
  g_tilde[0] = (h*h)*f(x0);
  u[0] = 0;
  u[-1] = 0;

  for(int i = 1; i < m_n - 1 ; i++){
    xi = x0 + (i*h);
    gi = (h*h) * f(xi); //hvordan få h^2?
    g_tilde[i] = gi - (g_tilde[i-1] / d_tilde[i-1]);
    d_tilde[i] = - (i+1)/i; //skal ikke trenge å ha denne her?
    u_analytic[i] = u_func(xi);
  }

  for(int i = (m_n-1); i -- > 1;){
    u[i] = (g_tilde[i] - u[i+1])/ d_tilde[i];
    //cout << "ui = " << (u[i]) << endl;
    //cout << "g tilde = " << (g_tilde[i]) << endl;
    //cout << "d tilde = " << (d_tilde[i]) << endl;
  }

  for(int i = 0; i < m_n ; i++){
    cout << "ui = " << (u[i]) << endl;
  }

}
