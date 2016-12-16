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
  int N;
  std::cin >> N;
  int v = 0;
  while(N > 1) {
    if(N > 4 && N % 2 == 0) N = (N - 2) / 2 + 2;
    else N = N / 2 + N % 2;
    ++v;
  }
  std::cout << v << std::endl;
  return 0;
}
