#include <iostream>

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else

#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)

#endif

int main() {
  long N;
  std::cin >> N;
  long start[N];
  long max[N];
  long pairs = 0;
  long total_pairs;
  for(long i = 0; i < N; ++i) {
  }
  return 0;
}
