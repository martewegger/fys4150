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
void Class_name::Initialize(int n, double V(double rho_i, double omega_r), double omega_r, double rho_max){
  m_n = n;
  double rho0 = 0.;                            // Starting point
  double rho_n = rho_max;                        // End point
  double h = (rho_n - rho0)/(m_n+1);              // Steplength
  double a = -1./(h*h);
  double d = 2./(h*h);       // base value of diagonal elements

  m_A = mat(m_n,m_n, fill::zeros);
  for (int i = 0; i < m_n-1; i++){        // loop for filling matrix A
    double rho_i = rho0 + i*h;
    m_A(i,i+1) = a;              // A is 1 on the lower digonal
    m_A(i,i) = d + V(rho_i, omega_r);               // A is -2 on the diagonal
    m_A(i+1,i) = a;              // A is 1 on the upper diagonal
  }
  m_A(m_n-1,m_n-1) = d + V(rho_n, omega_r);     // the lower right value has to be filled outsite the loop
  eig_sym(m_eigvals_init, m_A);
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
  for ( int i = 0; i < m_n; i++ ) {
    //cout << i << endl;
    if ( i != m_k && i != m_l ) {
      a_ik = m_A(i,m_k);
      a_il = m_A(i,m_l);
      m_A(i,m_k) = c*a_ik - s*a_il; m_A(m_k,i) = m_A(i,m_k);
      m_A(i,m_l) = c*a_il + s*a_ik; m_A(m_l,i) = m_A(i,m_l);
    }
  }
}

void Class_name::Solver(){
  m_max = 1.;
  m_tolerance = 1.0E-10;
  int iterations = 0;
  int maxiter = 1E5;
  while ( m_max > m_tolerance && iterations <= maxiter) {
    Offdiag();
    Jacobi_rotate();
    iterations++;
  }
  cout<<"iterations= " << iterations<<endl;
}

void Class_name::test_eigvals(){
  int test_crit = 0;
  for (int i = 0; i < m_n; i++){
    double eigval_final = m_A(i,i);
    double rel_err = fabs((m_eigvals_init(i)-m_eigvals(i))/m_eigvals_init(i));
    if (rel_err>m_tolerance){
      cout << "Eigenvalues calculated differ from expected values" << endl;
      cout << "relative error = " << rel_err << endl;
      test_crit++;
    }
  }
  if (test_crit<1){
    cout << " Eigenvalues are consistent with expectations" << endl;
  }
}

void Class_name::test_eigvecs(){
  int test_crit = 0;
  for (int i = 0; i < m_n; i++){
    vec vec1 = m_eigvecs.col(i); // testing orthog of this vec with the othrs
    for (int j = i+1; j < m_n; j++){
      vec vec2 = m_eigvecs.col(j);
      double prod = dot(vec1,vec2);
      //cout << prod << endl;
      if (prod > m_tolerance){
        cout << "HeR eR dEt FuCk!!" << endl;
        test_crit++;
      }
    }
  }
  if (test_crit<1){
    cout << " Eigenvectors are orthogonal" << endl;
  }
}

void Class_name::Unit_test(){
  eig_sym(m_eigvals, m_eigvecs, m_A);
  test_eigvals();
  test_eigvecs();
}

void Class_name::rel_err_rho_max(string outfilename){
  vec lambda(4);
  lambda(0) = 3.;
  lambda(1) = 7.;
  lambda(2) = 11.;
  lambda(3) = 15.;
  double acum_rel_err = 0;
  double rel_err = 0;
  ofstream ofile;
  ofile.open(outfilename);
  for (int i = 0; i < 4; i++){
    rel_err = fabs((lambda(i)-m_eigvals(i))/lambda(i));
    acum_rel_err += rel_err;
    ofile << setw(15) << rel_err<< endl;
  }
  ofile << setw(15) << acum_rel_err<< endl;
  ofile.close();
}

void Class_name::rel_err_N(string outfilename){
  double tol = 1E-4;
  double rel_err = fabs((m_eigvals(0)-lambda)/lambda);
  cout << " diff " << rel_err << endl;
  ofstream ofile;
  ofile.open(outfilename);
  ofile << setw(15) << rel_err;
  ofile.close();
}


// Function writing results to file
void Class_name::Write_to_file(string filename){
  cout << m_A << endl;
  m_ofile.open(filename);
  m_ofile << setw(15) << " # Eigenvalue";
  m_ofile << setw(15) << " A_ii"<<endl;

  for (int i = 0; i< m_n; i++){
    m_ofile << setw(15) << setprecision(8) << m_eigvals[i];
    m_ofile << setw(15) << setprecision(8) << m_A(i,i)<<endl;
  }
  m_ofile.close();


}
