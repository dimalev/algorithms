// read teb complex numbers into matrix and compute it's summ

#include <iostream>
#include <complex>
#include "matrix.hpp"
#include "matrix-io.hpp"

void six() {
  Numeric_lib::Matrix<std::complex<double>> line(10);
  std::cout << "Enter 10 complex numbers ( '17', '(23)' and '(55,-3)' are examples of complex numbers:";
  std::cout << std::endl;
  std::cin >> line;
  std::complex<double> sum(0, 0);
  line.apply([&sum](std::complex<double> next) { sum += next; });
  std::cout << sum << std::endl;
}

void seven() {
  int n00, n01, n02, n10, n11, n12;
  std::cout << "Enter six ints: ";
  std::cin >> n00 >> n01 >> n02 >> n10 >> n11 >> n12;
  Numeric_lib::Matrix<int, 2> mat(2, 3);
  mat[0][0] = n00;
  mat[0][1] = n01;
  mat[0][2] = n02;
  mat[1][0] = n10;
  mat[1][1] = n11;
  mat[1][2] = n12;
  std::cout << mat << std::endl;
}

int main() {
  six();
  seven();
  return 0;
}
