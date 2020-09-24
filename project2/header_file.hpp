// Header file
// This is where we declare the class, its variables and functions/methods.

#ifndef HEADER_FILE_HPP
#define HEADER_FILE_HPP

#include <fstream>
#include <string>
#include <armadillo>

using namespace std;
using namespace arma;

class Class_name {
private:
  double m_max, m_k, m_l, m_tolerance;
  int m_n;
  ofstream m_ofile; //outfile
  mat m_A, m_S, m_eigvecs;
  vec m_eigvals_init , m_eigvals;


public:
  void Initialize(int n, double V(double rho_i, double omega_r), double omega_r, double rho_max);
  void Offdiag();
  void Solver();
  void Write_to_file(string filename);
  void Jacobi_rotate();
  void Unit_test();
  void test_eigvals();
  void test_eigvecs();
  void rel_err_rho_max(string outfilename);
};

#endif
