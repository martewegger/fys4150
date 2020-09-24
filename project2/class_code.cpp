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
void Class_name::Initialize(int n){
  m_n = n;
  m_x0 = 0.;                            // Starting point
  m_xn = 1.;                            // End point
  m_h = (m_xn - m_x0)/(m_n+1);              // Steplength
  m_a = -1./(m_h*m_h);
  m_d = 2./(m_h*m_h);

  //m_A = mat(m_n,m_n, fill::zeros);
  m_A = mat(m_n,m_n);
  //m_eigenvalue = new double[m_n];
  //m_eigenvector = new double[m_n];

  for (int i = 0; i < m_n-1; i++){        // loop for filling matrix A
    m_A(i,i+1) = m_a;              // A is 1 on the lower digonal
    m_A(i,i) = m_d;               // A is -2 on the diagonal
    m_A(i+1,i) = m_a;              // A is 1 on the upper diagonal
  }
  m_A(m_n-1,m_n-1) = m_d;     // the lower right value has to be filled outsite the loop
  eig_sym(m_eigvals_init, m_A);
  //cout << m_A << endl;

}

// Function for solving the general case:

void Class_name::Offdiag(){ // why are the pointers there?
  m_max = 0;
  for (int i = 0; i < m_n; ++i) {
    for ( int j = i+1; j < m_n; ++j) { // only searching through the upper offdiag part.
      double aij = fabs(m_A(i,j));
      if ( aij > m_max){
        m_max=aij; m_k=i;m_l=j;
        //cout << m_max << m_k << m_l << endl;
      }
    }
  }
}


void Class_name::Jacobi_rotate(){
  double s, c;

  if ( m_A(m_k,m_l) != 0.0 ) {
    double t, tau;
    tau = (m_A(m_l,m_l) - m_A(m_k,m_k))/(2*m_A(m_k,m_l));
      if ( tau >= 0 ) {
        t = 1.0/(tau + sqrt(1.0 + tau*tau));
      }
      else {
        t = -1.0/(-tau + sqrt(1.0 + tau*tau));
      }
    c = 1/sqrt(1+t*t);
    s = c*t;
  }
  else {
    c = 1.0;
    s = 0.0;
  }
  double a_kk, a_ll, a_ik, a_il, r_ik, r_il;
  a_kk = m_A(m_k,m_k);
  a_ll = m_A(m_l,m_l);
  m_A(m_k,m_k) = c*c*a_kk - 2.0*c*s*m_A(m_k,m_l) + s*s*a_ll;
  m_A(m_l,m_l) = s*s*a_kk + 2.0*c*s*m_A(m_k,m_l) + c*c*a_ll;
  m_A(m_k,m_l) = 0.0; // hard-coding non-diagonal elements by hand
  m_A(m_l,m_k) = 0.0; // same here
  for ( int i = 0; i < m_n-2; i++ ) {
    //cout << i << endl;
    if ( i != m_k && i != m_l ) {
      a_ik = m_A(i,m_k);
      a_il = m_A(i,m_l);
      m_A(i,m_k) = c*a_ik - s*a_il; m_A(m_k,i) = m_A(i,m_k);
      m_A(i,m_l) = c*a_il + s*a_ik; m_A(m_l,i) = m_A(i,m_l);
    }
    //  And finally the new eigenvectors

    //r_ik = m_S(i,m_k); r_il = m_S(i,m_l);
    //m_S(i,m_k) = c*r_ik - s*r_il;
    //m_S(i,m_l) = c*r_il + s*r_ik;
  }
}

void Class_name::Solver(){
  m_max = 1.;
  double tolerance = 1.0E-10;
  int iterations = 0;
  int maxiter = 1E3;
  while ( m_max > tolerance && iterations <= maxiter) {
    Offdiag();
    Jacobi_rotate();
    iterations++;
  }
  cout<<"iterations= " << iterations<<endl;
}

void Class_name::Unit_test(){
  eig_sym(m_eigvals,m_eigenvector,m_A);
  double tol = 1E-3;
  


}


// Function writing results to file
void Class_name::Write_to_file(string filename){
  cout << m_A << endl;
  m_ofile.open(filename);
  m_ofile << setw(15) << " # Eigenvalue";
  m_ofile << setw(15) << " A_ii"<<endl;

  for (int i = 0; i< m_n; i++){
    m_ofile << setw(15) << setprecision(8) << m_eigenvalue[i];
    m_ofile << setw(15) << setprecision(8) << m_A(i,i)<<endl;
  }
  m_ofile.close();


}
