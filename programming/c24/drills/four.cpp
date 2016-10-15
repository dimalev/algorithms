// read 10 floats, write into Matrix, output it
#include <iostream>
#include "matrix.hpp"
#include "matrix-io.hpp"

int main() {
  Numeric_lib::Matrix<double> mat(10);
  for(int i = 0; i < 10; ++i) {
    double num;
    std::cout << "Enter " << (i + 1) << "th number: ";
    std::cin >> num;
    mat(i) = num;
  }
  std::cout << mat << std::endl;
  return 0;
}
