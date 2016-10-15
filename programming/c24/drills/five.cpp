// compute multiplication table for [0..n) x [0..m)

#include <iostream>
#include "matrix.hpp"
#include "matrix-io.hpp"

int main() {
  int n, m;
  std::cout << "n = ";
  std::cin >> n;
  Numeric_lib::Matrix<int> vN(n);
  for(int i = 0; i < n; ++i) vN[i] = i;
  std::cout << "m = ";
  std::cin >> m;
  Numeric_lib::Matrix<int, 2> mNM(m, n);
  for(int i = 0; i < m; ++i) {
    mNM[i] = vN * i;
  }
  std::cout << mNM << std::endl;
  return 0;
}
