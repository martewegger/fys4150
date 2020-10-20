#include <iostream>
#include <cmath>
#include <string>
#include <ctime>
#include <armadillo>
#include <fstream>

using namespace std;
using namespace arma;




int main(int argc, char *argv[]) {
  vec a,b;
  a=b= vec(2, fill::zeros);
  a(0)=1;
  a(1) =2;
  a+=a;
  cout << a << endl;

}
