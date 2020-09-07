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

// Function initializing variables
void Class_Poisson_Dirichlet::Initialize(int n,int cond){
  m_cond = cond;
  x0 = 0.;                            // Starting point
  xn = 1.;                            // End point
  m_n = n;                            // Number of steps
  h = (xn - x0)/(m_n+1);              // Steplength

  // General case:
  a = new double[m_n];                // Lower diagonal elements
  b = new double[m_n];                // Diagonal elements
  c = new double[m_n];                // Upper diagonal elements
  b_tilde_gen = new double[m_n];      // Right hand side of equation
  m_v_gensol = new double[m_n];       // General solution
  m_x = new double[m_n];              // X array

  // Filling arrays
  for (int i = 0 ; i < m_n; i++){
    m_x[i] = x0 + (i+1)*h;

    a[i] = 1.;
    b[i] = -2.;
    c[i] = 1.;
  }

  // Special case:
  m_v_specsol = new double[m_n];      // Special solution
  b_tilde_spec = new double[m_n];     // Right hand side of equation
  v_analytic = new double[m_n];       // Analytic solution

}

// Function for solving the general case:
void Class_Poisson_Dirichlet::Function_general(double f(double xi), double v_func(double xi)){
  // Right hand side of equation
  for (int i = 0; i < m_n; i++){
    b_tilde_gen[i] = pow(h,2) * f(m_x[i]);
  }

  //Forward part:
  for(int i = 1; i < m_n; i++){
    b_tilde_gen[i] = b_tilde_gen[i] - ((b_tilde_gen[i-1]*a[i-1]) / b[i-1]);
    b[i] = b[i] - ((c[i-1]*a[i-1])/b[i-1]);
  }

  //Backward part:
  m_v_gensol[m_n-1] = b_tilde_gen[m_n-1]/b[m_n-1];    // Boundary condition
  for (int i = (m_n-2); i >= 0; i--){
    m_v_gensol[i] = (b_tilde_gen[i] - (c[i]*m_v_gensol[i+1]))/b[i];
  }

}

// Function for solving the special case:
void Class_Poisson_Dirichlet::Function_special(double f(double xi), double v_func(double xi)){
  // Right hand side of equation
  b_tilde_spec[0] = pow(h,2)*f(m_x[0]);

  //Forward part:
  for(int i = 1; i < m_n; i++){
    b_tilde_spec[i] = pow(h,2) * f(m_x[i]);
    b_tilde_spec[i] += (b_tilde_spec[i-1]*(i) / (double)(i+1));
  }

  //Backward part:
  m_v_specsol[m_n-1] = -(b_tilde_spec[m_n-1]*m_n)/(m_n+1);  // Boundary condition
  for (int i = (m_n-2); i >= 0; i--){
    m_v_specsol[i] = -1.*(b_tilde_spec[i] - m_v_specsol[i+1])*(1.*(i+1)/ (i+2));
  }

}

// Function for computing and printing relative errors
void Class_Poisson_Dirichlet::print_relative_error(double v_func(double xi)){
  double highnumber = 0.;                 // Max error
  double error = 0.;                      // Error

  for (int i = 0; i < m_n;i++){
    v_analytic[i] = v_func(m_x[i]);       // Exact solution
    if (v_analytic[i] != 0){
      error = abs((m_v_specsol[i] - v_analytic[i])/v_analytic[i]);
    }
    if (error > highnumber){
      highnumber = error;

    }
  }
  cout << "log(h) = " << log10(h) << " log_error = " << log10(highnumber) << endl;
}

// Function for computing the LU decomposition
void Class_Poisson_Dirichlet::lu_decomp(double f(double xi)){
  cout << "here" << endl;
  mat A = mat(m_n,m_n);
  mat L,U;
  vec q = vec(m_n);
  A = A.fill(0.0);
  A(0,0) = 1.;
  for (int i = 0; i < m_n-1; i++){
    A(i,i+1) = 1.;
    A(i,i) = -2.;
    A(i+1,i) = 1.;
  }
  A(m_n-1,m_n-1) = -2.;

  for (int i = 0; i < m_n; i++){
    q[i] = pow(h,2)*f(m_x[i]);
  }
  lu(L,U,A);
  y = solve(L,q);       // solving Ly = q
  u_LU = solve(U,y);    // solving Ux = y
}

// FUnction writing results to file
void Class_Poisson_Dirichlet::Write_to_file(string filename){

    m_ofile.open(filename);
    //m_ofile <<'#'<< 'x' <<  "               " << "gen sol" << "         " << "spec sol" << "     "<< "analytic u" <<  endl;
    //m_ofile << m_x[0] <<  "  " << m_v_gensol[0] << "     " << m_v_specsol[0] << "            "<< v_analytic[0] << endl;
    m_ofile << setw(15) << "# x";
    m_ofile << setw(15) << " gen sol";
    m_ofile << setw(15) << " spec sol";
    if (m_n < m_cond){
      m_ofile << setw(15) << " LU decomp";
    }
    m_ofile << setw(15) << "analytic " << endl;

    m_ofile << setw(15) << setprecision(8) << m_x[0];
    m_ofile << setw(15) << setprecision(8) << m_v_gensol[0];
    m_ofile << setw(15) << setprecision(8) << m_v_specsol[0];
    if (m_n < m_cond){
      m_ofile << setw(15) << setprecision(8) << u_LU(0);
    }
    m_ofile << setw(15) << setprecision(8) << v_analytic[0]<<endl;
    for (int i = 1; i < m_n; i++){
      m_ofile << setw(15) << setprecision(8) << m_x[i];
      m_ofile << setw(15) << setprecision(8) << m_v_gensol[i];
      m_ofile << setw(15) << setprecision(8) << m_v_specsol[i];
      if (m_n < m_cond){
        m_ofile << setw(15) << setprecision(8) << u_LU(i);
      }
      m_ofile << setw(15) << setprecision(8) << v_analytic[i] <<endl;
      //m_ofile << m_x[i] <<  "     " << m_v_gensol[i]<< "     " << m_v_specsol[i] << "     "<< v_analytic[i] << endl;
    }
    m_ofile.close();

}
