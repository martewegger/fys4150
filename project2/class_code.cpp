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
void Class_Poisson_Dirichlet::Initialize(int n){
  m_n = n;
  a = new double[m_n];                // Lower diagonal elements
  d = new double[m_n];                // Diagonal elements

}

// Function for solving the general case:

void Class_name::Offdiag(){ // why are the pointers there?
  m_max = 0
  for (int i = 0; i < m_n; ++i) {
    for ( int j = i+1; j < m_n; ++j) { // only searching through the upper offdiag part.
      double aij = fabs(A(i,j));
      if ( aij > m_max){
        m_max=aij; m_k=i;m_l=j;
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
  m_A(m_k,m_l) = 0.0; // hard-coding non-diagonal elements by hand A(l,k) = 0.0; // same here
  for ( int i = 0; i < m_n; i++ ) {
    if ( i != m_k && i != m_l ) {
      a_ik = m_A(i,m_k);
      a_il = m_A(i,m_l);
      m_A(i,m_k) = c*a_ik - s*a_il; m_A(m_k,i) = m_A(i,m_k);
      m_A(i,m_l) = c*a_il + s*a_ik; m_A(m_l,i) = m_A(i,m_l);
    }
    //  And finally the new eigenvectors
    r_ik = m_S(i,m_k); r_il = m_S(i,m_l);
    m_S(i,m_k) = c*r_ik - s*r_il;
    m_S(i,m_l) = c*r_il + s*r_ik;
  }
}

void Class_name::Solver(){
  double tolerance = 1.0E-10;
  int iterations = 0;
  int maxiter = 1E3
  while ( m_max > tolerance && iterations <= maxiter) {
    Offdiag();
    Jacobi_rotate();
    iterations++;
  }
}

// Function writing results to file
void Class_Poisson_Dirichlet::Write_to_file(string filename){

    m_ofile.open(filename);
    m_ofile << setw(15) << "# x";

    m_ofile << setw(15) << setprecision(8) << m_x[0];
    m_ofile.close();

}
