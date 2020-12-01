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
  vec m_u_old, m_u, m_r, m_a, m_b, m_c;
  ofstream m_ofile;

public:
  void Initialise(double T_end, double dt, double dx);
  void ForwardEuler();
  void Solver();
  void Thomas();
  void Crank_Nicolsen();
  void Write_to_file();
};
#endif
