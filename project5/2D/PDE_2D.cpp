// class file
// This is where all functions are specified.

#include "PDE_2D.hpp"
#include <armadillo>
#include <iostream>
#include <cmath>
using namespace std;
using namespace arma;


// Function initializing variables, initializeren min
void PDE_2D::Initialise(double T_end, double dt, double dxy){
  double xy0 = 0;
  double xy1 = 1;
  m_Nxy = int((xy1-xy0)/dxy+1);
  m_Nt = int(T_end/dt+1);
  m_alpha = dt/pow(dxy,2);

  m_u_old = mat(m_Nxy, m_Nxy, fill::zeros);
  m_u = mat(m_Nxy,m_Nxy, fill::zeros);
  //Setting boundary conditions (unnecessary bc of fill::zeros)
  for (int i = 1;i<m_Nxy;i++){
    m_u_old(0,i) =0;
    m_u_old(m_Nxy-1,i) =0;
    m_u_old(i,0) =0;
    m_u_old(i,m_Nxy-1) =0;
  }
  int indx = int(m_Nxy/2);
  m_u_old(indx,indx) = 1.;
  m_u_old(indx,indx+1) = 1.;
  m_u_old(indx+1,indx+1) = 1.;
  m_u_old(indx+1,indx) = 1.;

  //Praparing a file to write in.
  m_ofile.open("data_2D.txt");
  m_ofile << "#x-dim along the horizontal axis, and y-dim along the vertical axis"<<endl;
}

void PDE_2D::Write_to_file(){
  for (int yj=0; yj<m_Nxy;yj++){
    for (int xi=0; xi<m_Nxy;xi++){
      m_ofile << setw(17) << setprecision(8) << m_u(xi,yj);
    }
    m_ofile<< endl;
  }
}


void PDE_2D::ForwardEuler(){

  for (int ti=0; ti<m_Nt;ti++){
    for (int xi=1; xi<m_Nxy-1;xi++){ //not looping over the first or last point
      for (int yj=1; yj<m_Nxy-1; yj++){
        m_u(xi,yj) = m_alpha * (m_u_old(xi,yj+1) + m_u_old(xi,yj-1) + m_u_old(xi+1,yj) + m_u_old(xi-1, yj)) + (1-4.*m_alpha)*m_u_old(xi,yj);
      }
    }
    for (int yj=1; yj<m_Nxy-1;yj++){
      for (int xi=1; xi<m_Nxy-1;xi++){
        m_u_old(xi,yj) = m_u(xi,yj);
      }
    }
  }
  Write_to_file();
}
