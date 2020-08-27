// Header file
// This is where we declare the class, its variables and functions/methods.

#ifndef HEADER_FILE_HPP
#define HEADER_FILE_HPP

class Classname {
private:
  double gi, xi, di, ei, x0, xn, h;
  int m_n;

public:

  void Initialize(int n);
  void Function(double f(double xi), double u_func(double xi));
  //void Print();
};

#endif
