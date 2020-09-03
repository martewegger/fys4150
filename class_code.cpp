// class file
// This is where all functions are specified.

#include "header_file.hpp"
#include <iostream>
#include <cmath>
#include <fstream>
#include <string>

using namespace std;

void Classname::Initialize(int n){

  x0 = 0.;
  xn = 1.;
  m_n = n;
  h = (xn - x0)/(m_n+2);  //steplength

  // General case:
  a = new double[m_n];
  b = new double[m_n];
  c = new double[m_n];
  b_tilde = new double[m_n];
  m_v_gensol = new double[m_n];      //solution
  m_x_gen = new double[m_n];
  v_analytic = new double[m_n];
  for (int i =0 ; i<m_n; i++){
    a[i]=1.;
    b[i]=-2.;
    c[i]=1.;
  }

  // Special case:
  di = -2.;
  ei = 1.;
  m_u_specsol = new double[m_n]; //allokere minne
  m_x_spec = new double[m_n]; //deklarerer array x med lengde m_n
  g_tilde = new double[m_n];
  u_analytic = new double[m_n];


}



// General:
void Classname::Function_general(double f(double xi), double u_func(double xi)){

  b_tilde[0] = pow(h,2) * f(x0+h);

  for (int i = 0; i< m_n;i++){
    b_tilde[i] = pow(h,2) * f(x0+h*i);
  }

  //Forward part:
  for(int i = 1; i < m_n; i++){
    m_x_gen[i] = x0 + (i+1)*h;
    b_tilde[i] = b_tilde[i] - ((b_tilde[i-1]*a[i-1]) / b[i-1]);
    b[i] = b[i] - ((c[i-1]*a[i-1])/b[i-1]);
    v_analytic[i] = u_func(m_x_gen[i]);
  }

  //Backward part:
  m_v_gensol[m_n-1] =  b_tilde[m_n-1]/b[m_n-1];
  for (int i = (m_n-2); i >= 0; i--){
    m_v_gensol[i] = (b_tilde[i]-(c[i]*m_v_gensol[i+1]))/b[i];
  }

}

// Special:
void Classname::Function_special(double f(double xi), double u_func(double xi)){

  g_tilde[0] = pow(h,2)*f(x0+h); //må ha denne her fordi vi bruker f, why h, skal være x0??

  //Forward part:
  for(int i = 1; i < m_n; i++){
    m_x_spec[i] = x0 + (i+1)*h;
    g_tilde[i] = pow(h,2) * f(m_x_spec[i]);
    g_tilde[i] += (g_tilde[i-1]*(i-1) / (double)(i));
    u_analytic[i] = u_func(m_x_spec[i]);
  }

  //Backward part:
  m_u_specsol[m_n-1] =  -(g_tilde[m_n-1]*m_n)/(m_n+1);
  for (int i = (m_n-2); i >= 0; i--){
    m_u_specsol[i] = -1.* (g_tilde[i] - m_u_specsol[i+1])*i / (i+1);
  }

}


void Classname::Write_to_file(string filename){

    m_ofile.open(filename);
    m_ofile <<'#'<< 'x' <<  "               " << "gen sol" << "         " << "spec sol" << "     "<< "analytic u" <<  endl;
    m_ofile << m_x_spec[0] <<  "               " << m_v_gensol[0] << "     " << m_u_specsol[0] << "            "<< u_analytic[0] << endl;
    for (int i = 1; i < m_n; i++){

      m_ofile << m_x_spec[i] <<  "     " << m_v_gensol[i]<< "     " << m_u_specsol[i] << "     "<< u_analytic[i] << endl;
    }
    m_ofile.close();

}

void Classname::print_relative_error(){
  double highnumber=0.;
  double error=0.;
  for (int i=0; i<m_n;i++){
    if (u_analytic[i]!=0){
      error=sqrt(pow((m_u_specsol[i]-u_analytic[i])/u_analytic[i],2));
    }
    if (error > highnumber){
      highnumber=error;
    }
  }
  cout << "log(h)= "<< log10(h) << " log_error= " << log10(highnumber) << endl;
}
