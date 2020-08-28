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
  double *m_u, *m_x, *g_tilde, *d_tilde, *u_analytic;
  int m_n;
  ofstream m_ofile; //outfile

public:

  void Initialize(int n);
  void Function(double f(double xi), double u_func(double xi));
  void Write_to_file(string filename);
  //void Print();
};

#endif
