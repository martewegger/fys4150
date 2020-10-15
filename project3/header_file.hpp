// Header file
// This is where we declare the class, its variables and functions/methods.

#ifndef HEADER_FILE_HPP
#define HEADER_FILE_HPP

#include <fstream>
#include <string>
#include <armadillo>

using namespace std;
using namespace arma;

class Class_name{
private:
    double m_vx0, m_vy0, m_h;
    vec m_x, m_y;
    int m_N;

public:
    void Initialize(double vx0, double vy0, double h, double T_end);
    void Solve(vec chosen_method(vec pos_obj1, vec sun_pos, vec old_vel, double h, double M, int beta, vec accel_func(double M, vec pos_obj1, vec pos_obj2, int beta)), vec accel_func(double M, vec pos_obj1, vec pos_obj2, int beta));
    void Write_to_file(string filename);
};
#endif
