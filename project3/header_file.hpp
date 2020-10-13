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
  double m_vx0, m_vy0;
  vec m_x, m_y;
  int m_N;

public:
  void Initialize(int N);
  void solve(double T_end, double method, vec accel_func(double M, vec pos_obj1, vec pos_obj2, int beta));
  void Write_to_file(string filename);
};

class Methods {
public:
  vec ForwardEuler(vec pos_obj1, vec pos_obj2, vec vel, double h, double M, int beta, vec acceleration(double M, vec  pos_obj1, vec pos_obj2, int beta));
  vec Verlet(vec pos_obj1, vec pos_obj2, vec vel, double h, double M, int beta, vec acceleration(double M, vec  pos_obj1, vec pos_obj2, int beta));
};

#endif
