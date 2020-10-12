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
  double m_x0, m_y0;
  double *m_x, *m_y;
  int m_N;

public:
  void Initialize(int n, double V(double rho_i));
  void solve(int N, double T_end, double method, double accel_func(double M, double pos_obj1, double pos_obj2, int beta));
  void Write_to_file(string filename);
};

class Methods {
public:
  double ForwardEuler(double pos_obj1, double pos_obj2, double vel, double h, double acceleration(double M, double  pos_obj1, double pos_obj2, int beta));
  double Verlet(double pos_obj1, double pos_obj2, double vel, double h, double acceleration(double M, double  pos_obj1, double pos_obj2, int beta));
};

#endif
