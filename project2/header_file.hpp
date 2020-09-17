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
  double x0;
  double *m_x;
  int m_n;
  ofstream m_ofile; //outfile
  vec u_LU;

public:
  void Initialize(int n,int cond);
  // void FUNCTION();
  void Write_to_file(string filename);
};

#endif
