// print sizes of different matrices (in elements and bytes)

#include <iostream>
#include <typeinfo>
#include "matrix.hpp"

// template<class T, int D>
// void print(Numeric_lib::Matrix<T, D> mat) {
//   std::cout << "Matrix of type " << typeid(T).name()
//             << " and multiple dimentions has size " << sizeof(mat) << std::endl;
// }

template<class T>
void print(Numeric_lib::Matrix<T, 1> mat) {
  std::cout << "Vector of type " << typeid(T).name()
            << " and length " << mat.size() << " has size " << sizeof(mat) << std::endl;
}

template<class T>
void print(Numeric_lib::Matrix<T, 2> mat) {
  std::cout << "Matrix of type " << typeid(T).name()
            << " and size " << mat.dim1() << "x" << mat.dim2() << " = " << mat.size()
            << " has size " << sizeof(mat) << std::endl;
}

template<class T>
void print(Numeric_lib::Matrix<T, 3> mat) {
  std::cout << "Matrix of type " << typeid(T).name()
            << " and size " << mat.dim1() << "x" << mat.dim2() << "x" << mat.dim3() << " = " << mat.size()
            << " has size " << sizeof(mat) << std::endl;
}

int main() {
  Numeric_lib::Matrix<int> a(10);
  Numeric_lib::Matrix<int> b(100);
  Numeric_lib::Matrix<double> c(10);
  Numeric_lib::Matrix<int, 2> d(10, 10);
  Numeric_lib::Matrix<int, 3> e(10, 10, 10);
  print(a);
  print(b);
  print(c);
  print(d);
  print(e);
  return 0;
}
