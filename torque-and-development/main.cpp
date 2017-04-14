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

void solve(int test) {
  int n, m, clib, croad;
  std::cin >> n >> m >> clib >> croad;
  
}

int main() {
  UNIT_TESTS();
  int T;
  std::cin >> T;
  for(int t = 0; t < T; ++t) {
    solve(t);
  }
  return 0;
}
