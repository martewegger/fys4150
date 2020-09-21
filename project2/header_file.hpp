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
  double m_max, m_k, m_l,a,d, m_x0, m_xn, m_h, m_d,m_a;
  double *m_eigenvalue, *m_eigenvector;
  int m_n;
  ofstream m_ofile; //outfile
  mat m_A,m_S;

public:
  void Initialize(int n);
  void Offdiag();
  void Solver();
  void Write_to_file(string filename);
  void Jacobi_rotate();
  void Eigenstuff_func();
};

#endif
