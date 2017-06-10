#include <iostream>
#include <limits>
#include <algorithm>

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

void solve(int t) {
  int N;
  std::cin >> N;
  int counts[1000], min = 1000;
  std::fill_n(counts, 1000, 0);
  for(int i = 0; i < N; ++i) {
    int c;
    std::cin >> c;
    ++counts[c];
    if(c < min) min = c;
  }
  int min_total = std::numeric_limits<int>::max();
  for(int target = min - 4; target <= min; ++target) {
    int total = 0;
    for(int i = 0; i < 1000; ++i) {
      if(counts[i] == 0) continue;
      int steps5 = (i - target) / 5;
      int steps2 = (i - target - steps5 * 5) / 2;
      int steps1 = i - target - steps5 * 5 - steps2 * 2;
      total += (steps5 + steps2 + steps1) * counts[i];
    }
    if(total < min_total) min_total = total;
  }
  std::cout << min_total << std::endl;
}

int main() {
#ifdef UNITS
  unit_tests();
  return 0;
#endif
  int T;
  std::cin >> T;
  for(int t = 0; t < T; ++t) solve(t);
  return 0;
}
