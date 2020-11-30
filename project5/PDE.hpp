// Header file
// This is where we declare the class, its variables and functions/methods.

#ifndef PDE_HPP
#define PDE_HPP

#include <fstream>
#include <string>
#include <iostream>
#include <cmath>
#include <random>
#include <armadillo>

using namespace std;
using namespace arma;


class PDE{
private:
  int m_Nx, m_Nt;
  double m_alpha;
  vec m_u_old, m_u, m_r;
  ofstream m_ofile;

public:
  void Initialise(double T_end, double dt, double dx);
  void ForwardEuler();
  void Crank_Nicolsen();
  void Write_to_file();
};
#endif
