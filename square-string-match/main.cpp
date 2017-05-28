#include <iostream>

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

constexpr int BUFFER_SIZE = 2000;
constexpr int MOD = 1e9 + 7;

int sum(const square &target, int row_start, int col_start,
        int rows, int cols) {
  int res = 0;
  for(int r = 0; r < rows; ++r) {
    for(int c = 0; c < cols; ++c) {
      res = (res + target.at(row_start + r, col_start + c)) % MOD;
    }
  }
  return res;
}

int compare_count = 0;

bool compare_at(const square &one, const square &two, int row, int col) {
  ++compare_count;
  return two.compare_at(one, row, col);
}

#ifdef UNITS
void unit_tests() {
  test_header("test units");
}
#endif

int main() {
#ifdef UNITS
  unit_tests();
  return 0;
#endif
  char buffer[BUFFER_SIZE];
  int pattern_rows, pattern_cols;
  std::cin >> pattern_rows >> pattern_cols;
  assert(pattern_cols < BUFFER_SIZE);
  square pattern(pattern_rows, pattern_cols);
  for(int r = 0; r < pattern_rows; ++r) {
    std::cin >> buffer;
    for(int c = 0; c < pattern_cols; ++c) {
      pattern.at(r, c) = buffer[c];
    }
  }
  int matrix_rows, matrix_cols;
  std::cin >> matrix_rows >> matrix_cols;
  assert(matrix_cols < BUFFER_SIZE);
  square matrix(matrix_rows, matrix_cols);
  for(int r = 0; r < matrix_rows; ++r) {
    std::cin >> buffer;
    for(int c = 0; c < matrix_cols; ++c) {
      matrix.at(r, c) = buffer[c];
    }
  }
  int target = sum(pattern, 0, 0, pattern.rows(), pattern.cols());
  TRACE_LINE("pattern sum: " << target);
  int dcols = matrix_cols - pattern_cols;
  int drows = matrix_rows - pattern_rows;
  int summs[dcols];
  summs[0] = sum(matrix, 0, 0, pattern.rows(), pattern.cols());
  TRACE_LINE("matrix at 0, 0: " << summs[0]);
  for(int c = 1; c < dcols; ++c) {
    int left = sum(matrix, 0, c - 1, pattern.rows(), 1);
    int right = sum(matrix, 0, c + pattern.cols() - 1, pattern.rows(), 1);
    summs[c] = ((MOD + summs[c - 1] - left) % MOD + right) % MOD;
    TRACE_LINE("matrix at 0, " << c << ": " << summs[c] <<
               " -" << left << " +" << right);
  }
  for(int c = 0; c < dcols; ++c) {
    if(summs[c] == target) {
      if(compare_at(pattern, matrix, 0, c)) {
        std::cout << 0 << " " << c << std::endl;
        TRACE_LINE("Total compares: " << compare_count);
        return 0;
      }
    }
  }
  for(int r = 1; r < drows; ++r) {
    for(int c = 0; c < dcols; ++c) {
      int up = sum(matrix, r - 1, c, 1, pattern.cols());
      int down = sum(matrix, r + pattern.rows() - 1, c, 1, pattern.cols());
      summs[c] = ((MOD + summs[c] - up) % MOD + down) % MOD;
      TRACE_LINE("matrix at " << r << ", " << c << ": " << summs[c] <<
                 " -" << up << " +" << down);
      if(summs[c] == target) {
        if(compare_at(pattern, matrix, r, c)) {
          std::cout << r << " " << c << std::endl;
          TRACE_LINE("Total compares: " << compare_count);
          return 0;
        }
      }
    }
  }
  std::cout << "Not found.\n";
  TRACE_LINE("Total compares: " << compare_count);
  return 0;
}
