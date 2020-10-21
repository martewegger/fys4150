#include <iostream>
#include <cmath>
#include <string>
#include <ctime>
#include <armadillo>
#include <fstream>

using namespace std;
using namespace arma;




int main(int argc, char *argv[]) {
  vec a_old,a_new,b;
  a_old=vec(2, fill::zeros);
  a_new=vec(2, fill::zeros);
  b= vec(2, fill::zeros);
  b(0) = 1;
  b(1) = 2;
  for (int i  = 0;i<4;i++){
    cout << a_old<<endl;
    a_old += b;
    //a_old = a_new;
    cout << a_old<<endl;

  }
  cout << "final"<<a_old << endl;

}
