// Header file
// This is where we declare the class, its variables and functions/methods.

#ifndef HEADER_FILE_HPP
#define HEADER_FILE_HPP

#include <fstream>
#include <string>
#include <armadillo>

using namespace std;
using namespace arma;

class Classname {
private:
  double gi, xi, di, ei, x0, xn, h;
  double *m_u_specsol, *m_u_gensol, *m_x, *g_tilde, *u_analytic, *v_analytic, *a, *b, *c, *q, *p, *b_tilde;
  int m_n;
  ofstream m_ofile; //outfile
  vec u_LU,y;
  int m_cond;

public:

  void Initialize(int n,int cond);
  void Function_special(double f(double xi), double u_func(double xi));
  void Function_general(double f(double xi), double u_func(double xi));
  void print_relative_error(double u_func(double xi));
  void lu_decomp(double f(double xi));
  void Write_to_file(string filename);
};

#endif
