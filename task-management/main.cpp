#include <iostream>
#include <algorithm>

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
  int N, res = 0;
  std::cin >> N;
  bool exist[N];
  std::fill_n(exist, N, false);
  for(int i = 0; i < N; ++i) {
    int v;
    std::cin >> v;
    --v;
    if(v == 0) {
      ++res;
    } else {
      if(!exist[v - 1]) {
        ++res;
      }
    }
    exist[v] = true;
  }
  std::cout << res << "\n";
  return 0;
}
