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
    double m_h, m_beta;
    vec m_x, m_y, m_vx, m_vy, m_mass;
    int m_N, m_Nbody;
    ofstream m_ofile;

public:
    void Initialize(double vx0, double vy0, double h, double T_end, double beta);
    void Solve(vec chosen_method(vec pos_obj1, vec sun_pos, vec old_vel, double h, double M, double beta, vec accel_func(double M, vec pos_obj1, vec pos_obj2, double beta)), vec accel_func(double M, vec pos_obj1, vec pos_obj2, double beta));
    void Write_to_file(string filename);
};
#endif
