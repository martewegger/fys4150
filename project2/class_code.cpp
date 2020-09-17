// class file
// This is where all functions are specified.

#include "header_file.hpp"
#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <armadillo>

using namespace std;
using namespace arma;

// Function initializing variables
void Class_Poisson_Dirichlet::Initialize(int n,int cond){
  m_cond = cond;
  x0 = 0.;                            // Starting point
  xn = 1.;                            // End point
  m_n = n;                            // Number of steps
  h = (xn - x0)/(m_n+1);              // Steplength

  // General case:
  a = new double[m_n];                // Lower diagonal elements
  d = new double[m_n];                // Diagonal elements

  // Filling arrays

}

// Function for solving the general case:
void Class_Poisson_Dirichlet::Function_general(){


}


// Function writing results to file
void Class_Poisson_Dirichlet::Write_to_file(string filename){

    m_ofile.open(filename);
    m_ofile << setw(15) << "# x";
    m_ofile << setw(15) << " gen sol";
    m_ofile << setw(15) << " spec sol";
    if (m_n < m_cond){
      m_ofile << setw(15) << " LU decomp";
    }
    m_ofile << setw(15) << "analytic " << endl;

    m_ofile << setw(15) << setprecision(8) << m_x[0];
    m_ofile << setw(15) << setprecision(8) << m_v_gensol[0];
    m_ofile << setw(15) << setprecision(8) << m_v_specsol[0];
    if (m_n < m_cond){
      m_ofile << setw(15) << setprecision(8) << u_LU(0);
    }
    m_ofile << setw(15) << setprecision(8) << v_analytic[0]<<endl;
    for (int i = 1; i < m_n; i++){
      m_ofile << setw(15) << setprecision(8) << m_x[i];
      m_ofile << setw(15) << setprecision(8) << m_v_gensol[i];
      m_ofile << setw(15) << setprecision(8) << m_v_specsol[i];
      if (m_n < m_cond){
        m_ofile << setw(15) << setprecision(8) << u_LU(i);
      }
      m_ofile << setw(15) << setprecision(8) << v_analytic[i] <<endl;
    }
    m_ofile.close();

}
