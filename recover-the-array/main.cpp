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
  int N, m = 0, t, K;
  std::cin >> N;
  for(int i = 0; i < N; ++i) {
    ++m;
    std::cin >> K;
    for(int j = 0; j < K; ++j, ++i) std::cin >> t;
  }
  std::cout << m << std::endl;
  return 0;
}
