// Header file
// This is where we declare the class, its variables and functions/methods.

#ifndef HEADER_FILE_HPP
#define HEADER_FILE_HPP

#include <fstream>
#include <string>
#include <armadillo>

using namespace std;
using namespace arma;

class Class_Poisson_Dirichlet {
private:
  double x0, xn, h, xi, gi, di, ei;
  double *m_x, *m_v_specsol, *m_v_gensol, *b_tilde_gen, *b_tilde_spec, *v_analytic, *a, *b, *c;
  int m_n, m_cond;
  ofstream m_ofile; //outfile
  vec u_LU,y;

public:
  void Initialize(int n,int cond);
  void Function_special(double f(double xi), double u_func(double xi));
  void Function_general(double f(double xi), double u_func(double xi));
  void print_relative_error(double u_func(double xi));
  void lu_decomp(double f(double xi));
  void Write_to_file(string filename);
};

#endif
