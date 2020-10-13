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
    double m_vx0, m_vy0;
    vec m_x, m_y;
    int m_N;

public:
    void Initialize(int N);
    //void Solve(double T_end, vec chosen_method(vec pos_obj1, vec sun_pos, vec old_vel, double h, double M, int beta, vec accel_func(double M, vec pos_obj1, vec pos_obj2, int beta)), vec accel_func(double M, vec pos_obj1, vec pos_obj2, int beta));
    void Solve(double T_end, vec accel_func(double M, vec pos_obj1, vec pos_obj2, int beta));
    vec ForwardEuler(vec pos_obj1, vec pos_obj2, vec vel, double h, double M, int beta, vec accel_func(double M, vec  pos_obj1, vec pos_obj2, int beta));
    vec Verlet(vec pos_obj1, vec pos_obj2, vec vel, double h, double M, int beta, vec accel_func(double M, vec  pos_obj1, vec pos_obj2, int beta));
    void Write_to_file(string filename);
};



#endif
