#include <iostream>
#include <algorithm>

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

void solve() {
  int rows, cols;
  std::cin >> rows >> cols;
  int A[1000];
  std::fill_n(A, 1000, 0);
  fr(i,0,rows * cols) {
    int a;
    std::cin >> a;
    A[a]++;
  }
  int s = 0, i = 0, m = (rows * cols) / 2 + 1;
  for(;;) {
    s += A[i];
    TRACE_LINE(i << ": " << A[i] << " (" << s << ")");
    if(s >= m) {
      std::cout << i << std::endl;
      return;
    }
    ++i;
  }
}

int main() {
#ifdef UNITS
  unit_tests();
  return 0;
#endif
  int T;
  std::cin >> T;
  fr(t,0,T) solve();
  return 0;
}
