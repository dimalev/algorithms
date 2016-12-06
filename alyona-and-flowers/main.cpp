#include <iostream>

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else

#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)
#define UNIT_TESTS()

#endif

void unit_tests() {
}

int main() {
  UNIT_TESTS();
  int n, m;
  std::cin >> n >> m;
  int summ = 0, summs[n + 1];
  summs[0] = 0;
  for(int i = 0; i < n; ++i) {
    int f;
    std::cin >> f;
    summ += f;
    summs[i + 1] = summ;
  }
  int total = 0;
  for(int i = 0; i < m; ++i) {
    int l, r;
    std::cin >> l >> r;
    total += std::max(summs[r] - summs[l - 1], 0);
  }
  std::cout << total << std::endl;
  return 0;
}
