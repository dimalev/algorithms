#include <iostream>
#include <cstdlib>
#include <initializer_list>

#include "square.h"

#ifdef UNITS
#include "../test/units.cpp"
#endif

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else
#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)
#endif

#ifdef UNITS
void unit_tests() {
  test_header("test units");
  square test{{'a', 'b', 'c'},
    {'d', 'e', 'f'}};
  std::cout << test.at(1, 2) << std::endl;
}
#endif

int main() {
#ifdef UNITS
  unit_tests();
  return 0;
#endif
  constexpr int pattern_rows = 30, pattern_cols = 30;
  constexpr int matrix_rows = 1000, matrix_cols = 1000;
  assert(pattern_rows <= matrix_rows);
  assert(pattern_cols <= matrix_cols);
  square pattern(pattern_rows, pattern_cols),
      matrix(matrix_rows, matrix_cols);
  for(int r = 0; r < matrix_rows; ++r) {
    for(int c = 0; c < matrix_cols; ++c) {
      matrix.at(r, c) = 'a' + (std::rand() % ('z' - 'a'));
    }
  }
  int result_r = std::rand() % (matrix_rows - pattern_rows + 1);
  int result_c = std::rand() % (matrix_cols - pattern_cols + 1);
  for(int r = 0; r < pattern_rows; ++r) {
    for(int c = 0; c < pattern_cols; ++c) {
      pattern.at(r, c) = 'a' + (std::rand() % ('z' - 'a'));
      matrix.at(result_r + r, result_c + c) = pattern.at(r, c);
    }
  }
  std::cout << "input:\n";
  std::cout << pattern_rows << " " << pattern_cols << std::endl;
  for(int r = 0; r < pattern_rows; ++r) {
    for(int c = 0; c < pattern_cols; ++c)
      std::cout << pattern.at(r, c);
    std::cout << "\n";
  }
  std::cout << matrix_rows << " " << matrix_cols << std::endl;
  for(int r = 0; r < matrix_rows; ++r) {
    for(int c = 0; c < matrix_cols; ++c)
      std::cout << matrix.at(r, c);
    std::cout << "\n";
  }
  std::cout << "output:\n";
  std::cout << result_r << " " << result_c << std::endl;
  return 0;
}
