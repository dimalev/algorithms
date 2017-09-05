#include <iostream>

#define fr(v,s,e) for(int v = s; v < e; ++v)
#define fl(v,s,e) for(int v = s; v > e; --v)

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
}
#endif

int main() {
#ifdef UNITS
  unit_tests();
  return 0;
#endif
  int N;
  std::cin >> N;
  int ones[N], zeroes[N], total_ones = 0, total_zeroes = 0;
  fr(i,0,N) {
    int v;
    std::cin >> v;
    if(v == 1) ++total_ones;
    else ++total_zeroes;
    ones[i] = total_ones;
    zeroes[i] = total_zeroes;
  }
  int max = std::max(total_ones, total_zeroes);
  fr(i,1,N) {
    int next = zeroes[i - 1] + total_ones - ones[i - 1];
    if(next > max) max = next;
  }
  std::cout << max << std::endl;
  return 0;
}
