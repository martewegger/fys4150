// class file
// This is where all functions are specified.

#include "PDE.hpp"
#include <armadillo>
#include <iostream>
#include <cmath>
using namespace std;
using namespace arma;


// Function initializing variables, initializeren min
void PDE::Initialise(double T_end, double dt, double dx){
  double x0 = 0;
  double x1 = 1;
  m_Nx = int((x1-x0)/dx+1);
  m_Nt = int(T_end/dt+1);
  m_u_old = vec(m_Nx, fill::zeros);
  m_u = vec(m_Nx, fill::zeros);
  m_u_old(m_Nx-1) = 1.;
  m_u(m_Nx-1) = 1.;
  m_r = vec(m_Nx+1, fill::zeros);
  m_alpha = dt/pow(dx,2);

  m_a = vec(m_Nx+1, fill::zeros);
  m_b = vec(m_Nx+1, fill::zeros);
  m_c = vec(m_Nx+1, fill::zeros);
  for (int i = 0 ; i < m_Nx; i++){
    m_a(i) = -m_alpha;
    m_b(i) = 1.+2*m_alpha;
    m_c(i) = -m_alpha;

  }
  //m_u = vec(m_N+1, fill::zeros);
  //double v; //du/dt for implicit BackwardEuler
  //Praparing a file to write in.
  m_ofile.open("data_1D.txt");
  m_ofile << "#x-values along the horizontal axis, and timesteps along the vertical axis"<<endl;
  //m_ofile << setw(17) << setprecision(8) << m_u_old(m_Nx);
}

void PDE::Write_to_file(){
  for (int i=0; i<m_Nx;i++){
    m_ofile << setw(17) << setprecision(8) << m_u(i);
  }
  m_ofile<< endl;
}
void PDE::ForwardEuler(){
  Write_to_file();
  for (int ti=0; ti<m_Nt;ti++){
    for (int xi=1; xi<m_Nx-1;xi++){ //not looping over the first or last point
      m_u(xi) = m_alpha*m_u_old(xi-1)+(1.-2.*m_alpha)*m_u_old(xi)+m_alpha*m_u_old(xi+1);
    }
    Write_to_file();
    for (int xi=1; xi<m_Nx-1;xi++){
      m_u_old(xi) = m_u(xi);
    }
  }
}

void PDE::Solver(){
  //Forward part:
  for(int i = 1; i < m_Nx-1; i++){
    m_b(i) = m_b(i) - ((m_c(i-1)*m_a(i-1))/m_b(i-1));
    m_r(i) = m_r(i) - ((m_r(i-1)*m_a(i-1)) / m_b(i-1));
    //m_b(i) = m_b(i) - ((m_c(i-1)*m_a(i-1))/m_b(i-1));
  }

  //Backward part:
  for (int i = (m_Nx-2); i >= 1; i--){
    m_u(i) = (m_r(i) - (m_c(i)*m_u(i+1)))/m_b(i);
  }
}


void PDE::Crank_Nicolsen(){
  for (int ti=0; ti<m_Nt;ti++){
    for (int i=1; i<m_Nx-1;i++){ //not looping over the end points
      //filling array with right hand side of equation
      m_r(i) = m_alpha*m_u_old(i-1)+(1.-2.*m_alpha)*m_u_old(i) + m_alpha*m_u_old(i+1);
    }
    m_r(0) = 0;
    m_r(m_Nx)= 0;
    Solver();
    Write_to_file();
    for (int xi=1; xi<m_Nx-1;xi++){
      m_u_old(xi) = m_u(xi);
    }
  }
}
