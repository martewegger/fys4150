// class file
// This is where all functions are specified.

#include "header_file.hpp"
#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <armadillo>

using namespace std;
using namespace arma;
//kommentar

void Classname::Initialize(int n,int cond){
  m_cond=cond;
  x0 = 0.;
  xn = 1.;
  m_n = n;
  h = (xn - x0)/(m_n+1);  //steplength

  // General case:
  a = new double[m_n];
  b = new double[m_n];
  c = new double[m_n];
  b_tilde = new double[m_n];
  m_u_gensol = new double[m_n];      //solution
  m_x = new double[m_n];
  v_analytic = new double[m_n];
  for (int i =0 ; i<m_n; i++){
    m_x[i] = x0 + (i+1)*h;

    a[i]=1.;
    b[i]=-2.;
    c[i]=1.;
  }

  // Special case:
  di = -2.;
  ei = 1.;
  m_u_specsol = new double[m_n]; //allokere minne
  g_tilde = new double[m_n];
  u_analytic = new double[m_n];


}

// General:
void Classname::Function_general(double f(double xi), double u_func(double xi)){
  for (int i = 0; i< m_n;i++){
    b_tilde[i] = pow(h,2) * f(m_x[i]);
  }

  //Forward part:
  for(int i = 1; i < m_n; i++){
    b_tilde[i] = b_tilde[i] - ((b_tilde[i-1]*a[i-1]) / b[i-1]);
    b[i] = b[i] - ((c[i-1]*a[i-1])/b[i-1]);
    //v_analytic[i] = u_func(m_x[i]);
  }

  //Backward part:
  m_u_gensol[m_n-1] =  b_tilde[m_n-1]/b[m_n-1];
  for (int i = (m_n-2); i >= 0; i--){
    m_u_gensol[i] = (b_tilde[i]-(c[i]*m_u_gensol[i+1]))/b[i];
  }

}

// Special:
void Classname::Function_special(double f(double xi), double u_func(double xi)){

  g_tilde[0] = pow(h,2)*f(m_x[0]); //må ha denne her fordi vi bruker f, why h, skal være x0??

  //Forward part:
  //u_analytic[0] = u_func(m_x[0]);
  for(int i = 1; i < m_n; i++){
    g_tilde[i] = pow(h,2) * f(m_x[i]);
    g_tilde[i] += (g_tilde[i-1]*(i) / (double)(i+1));
    //u_analytic[i] = u_func(m_x[i]);
  }

  //Backward part:
  m_u_specsol[m_n-1] =  -(g_tilde[m_n-1]*m_n)/(m_n+1);
  for (int i = (m_n-2); i >= 0; i--){
    m_u_specsol[i] = -1.* (g_tilde[i] - m_u_specsol[i+1])*(1.*(i+1)/ (i+2));
  }

}


void Classname::print_relative_error(double u_func(double xi)){
  double highnumber=0.;
  double error=0.;
  for (int i=0; i<m_n;i++){
    u_analytic[i]=u_func(m_x[i]);
    if (u_analytic[i]!=0){
      //error=sqrt(pow((m_u_specsol[i]-u_analytic[i])/u_analytic[i],2));
      error=abs((m_u_specsol[i]-u_analytic[i])/u_analytic[i]);
    }
    if (error > highnumber){
      highnumber=error;

    }
  }
  cout << "log(h)= "<< log10(h) << " log_error= " << log10(highnumber) << endl;
}


void Classname::lu_decomp(double f(double xi)){
  cout<<"here"<<endl;
  mat A = mat(m_n,m_n);
  mat L,U;
  vec q = vec(m_n);
  A=A.fill(0.0);
  A(0,0)=1.;
  for (int i=0;i<m_n-1;i++){
    A(i,i+1)=1.;
    A(i,i)=-2.;
    A(i+1,i)=1.;
  }
  A(m_n-1,m_n-1)=-2.;

  for (int i=0;i<m_n;i++){
    q[i]=h*h*f(m_x[i]);
  }
  lu(L,U,A);
  y = solve(L,q); // solving Ly = q
  u_LU = solve(U,y); // solving Ux = y
}


void Classname::Write_to_file(string filename){

    m_ofile.open(filename);
    //m_ofile <<'#'<< 'x' <<  "               " << "gen sol" << "         " << "spec sol" << "     "<< "analytic u" <<  endl;
    //m_ofile << m_x[0] <<  "  " << m_u_gensol[0] << "     " << m_u_specsol[0] << "            "<< u_analytic[0] << endl;
    m_ofile << setw(15) << "# x";
    m_ofile << setw(15) << " gen sol";
    m_ofile << setw(15) << " spec sol";
    if (m_n<m_cond){
      m_ofile << setw(15) << " LU decomp";
    }
    m_ofile << setw(15) << "analytic "<<endl;


    m_ofile << setw(15) << setprecision(8) << m_x[0];
    m_ofile << setw(15) << setprecision(8) << m_u_gensol[0];
    m_ofile << setw(15) << setprecision(8) << m_u_specsol[0];
    if (m_n<m_cond){
      m_ofile << setw(15) << setprecision(8) << u_LU(0);
    }
    m_ofile << setw(15) << setprecision(8) << u_analytic[0]<<endl;
    for (int i = 1; i < m_n; i++){
      m_ofile << setw(15) << setprecision(8) << m_x[i];
      m_ofile << setw(15) << setprecision(8) << m_u_gensol[i];
      m_ofile << setw(15) << setprecision(8) << m_u_specsol[i];
      if (m_n<m_cond){
        m_ofile << setw(15) << setprecision(8) << u_LU(i);
      }
      m_ofile << setw(15) << setprecision(8) << u_analytic[i]<<endl;
      //m_ofile << m_x[i] <<  "     " << m_u_gensol[i]<< "     " << m_u_specsol[i] << "     "<< u_analytic[i] << endl;
    }
    m_ofile.close();

}
