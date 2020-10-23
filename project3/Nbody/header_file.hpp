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
    double m_h, m_beta, m_G;
    vec m_x, m_y, m_vx_old, m_vy_old,m_vx_new, m_vy_new, m_acc, m_mass;
    int m_N, m_Nbody;
    ofstream m_ofile;
    string m_filename,m_mercury;

public:
    void Initialize(double h, double T_end, string filename, double beta);
    void Write_to_file();
    void diff_eq(int i, int j);
    void Verlet();
    void Solve();

};
#endif
