// Header file
// This is where we declare the class, its variables and functions/methods.

#ifndef HEADER_FILE_HPP
#define HEADER_FILE_HPP

#include <fstream>
#include <string>

using namespace std;

class Classname {
private:
  double gi, xi, di, ei, x0, xn, h;
  double *m_u_specsol, *m_v_gensol, *m_x_spec, *m_x_gen, *g_tilde, *u_analytic, *v_analytic, *a, *b, *c, *q, *p, *b_tilde;
  int m_n;
  ofstream m_ofile; //outfile

public:

  void Initialize(int n);
  void Function_special(double f(double xi), double u_func(double xi));
  void Function_general(double f(double xi), double u_func(double xi));
  void Write_to_file(string filename);
  void print_relative_error();
  //void Print();
};

#endif
