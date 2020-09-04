#include "header_file.hpp"
#include <iostream>
#include <cmath>
#include <fstream> //til plottegreiene
#include <string>
#include <armadillo>

using namespace std;
using namespace arma;
double f(double xi);

int main(int argc, char const *argv[]) {
  int n=10;
  double x0=0;
  double xn=1;
  double h = (xn - x0)/(n+2); // sjekk denne
  mat A = mat(n,n);
  mat L,U;
  vec x,y;
  vec q = vec(n);
  A=A.fill(0.0);
  A(0,0)=1.;
  for (int i=0;i<n-1;i++){
    A(i,i+1)=1.;
    A(i,i)=-2.;
    A(i+1,i)=1.;
  }
  A(n-1,n-1)=-2.;

  for (int i=0;i<n;i++){
    q[i]=h*h*f(x0+i*h);
  }
  lu(L,U,A);

  y = solve(L,q); // solving Ly = q
  x = solve(U,y); // soling Ux = y

  cout << x << endl;


  return 0;
}
double f(double xi){
  return -100*exp(-10*xi);
}
