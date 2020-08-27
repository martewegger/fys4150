// Header file
// This is where we declare the class, its variables and functions/methods.

#ifndef HEADER_FILE_HPP
#define HEADER_FILE_HPP

class Trapezoidal {
private:
  double m_a, m_b, m_I, m_stepsize;
  int m_N;

public:

  void Initialize(double a, double b, int N);
  void Integrate(double f(double x));
  void Print();
};

#endif
