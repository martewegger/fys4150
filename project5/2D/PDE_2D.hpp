// Header file
// This is where we declare the class, its variables and functions/methods.

#ifndef PDE_2D_HPP
#define PDE_2D_HPP

#include <fstream>
#include <string>
#include <iostream>
#include <cmath>
#include <random>
#include <armadillo>

using namespace std;
using namespace arma;


class PDE_2D{
private:
  int m_Nxy, m_Nt;
  double m_alpha;
  mat m_u_old, m_u;
  ofstream m_ofile;

public:
  void Initialise(double T_end, double dt, double dxy);
  void ForwardEuler();
  void Write_to_file();
};
#endif
