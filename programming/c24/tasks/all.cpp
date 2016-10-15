#include <iostream>
#include <array>
#include "../drills/matrix.hpp"
#include "../drills/matrix-io.hpp"

int tripple(int &elem) { return elem *= 3; }

// make a function which can be used in apply(function, Matrix) and Matrix::apply(function)
// explain why this is a bad idea
void one() {
  int val[] = {1,2,3,4,5,6,7,8,9,10};
  Numeric_lib::Matrix<int, 1> line{val};
  Numeric_lib::Matrix<int, 1> result{val};
  line.apply(tripple);
  result = Numeric_lib::apply(tripple, line);
  std::cout << line << std::endl;
  std::cout << result << std::endl;
}

template<class T> struct Tripple {
  int operator()(int &elem) { return elem *= 3; }
};

// do one but with function Objects
void two() {
  int val[] = {1,2,3,4,5,6,7,8,9,10};
  Tripple<int> trippler_obj;
  Numeric_lib::Matrix<int, 1> line{val};
  Numeric_lib::Matrix<int, 1> result{val};
  line.apply(trippler_obj);
  result = Numeric_lib::apply(trippler_obj, line);
  std::cout << line << std::endl;
  std::cout << result << std::endl;
}

int main() {
  one();
  two();
}
