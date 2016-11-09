#include <iostream>

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else

#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)

#endif

#include "matrix.hpp"
#include "matrix-io.hpp"

int main() {
  int n;
  std::cin >> n;
  Numeric_lib::Matrix<float, 2> M{n, n};
  std::cin >> M;
  Numeric_lib::Matrix<float, 1> b{n};
  std::cin >> b;
  for(Numeric_lib::Index i = 0; i < n - 1; ++i) {
    for(Numeric_lib::Index j = i + 1; j < n; ++j) {
      b[j] -= b[i] / M[i][i] * M[j][i];
      M[j].slice(i) = Numeric_lib::scale_and_add(M[i].slice(i), -M[j][i] / M[i][i], M[j].slice(i));
    }
  }
  for(Numeric_lib::Index i = n - 1; i >= 0; --i) {
    b[i] /= M[i][i];
    M[i] /= M[i][i];
    for(Numeric_lib::Index j = i - 1; j >= 0; --j) {
      b[j] -= b[i] / M[i][i] * M[j][i];
      M[j].slice(i) = Numeric_lib::scale_and_add(M[i].slice(i), -M[j][i] / M[i][i], M[j].slice(i));
    }
  }
  std::cout << b;
  return 0;
}
