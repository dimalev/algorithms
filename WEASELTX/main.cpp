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

constexpr long long max_m = 0b1100000000000000000000000000000000000000000000000000000000000;
constexpr long long max_d = 59;

int check(long long a, long long b) {
  long long M = max_m;
  long long D = max_d;
  long long x, y;
  while(D > 0) {
    x = (a & M) >> D;
    y = (b & M) >> D;
    if(y > x) return 0;
    // std::cout << M << ", " << D << ": "
    //           << x << " vs " << y << std::endl;
    --D; M >>= 1;
  }
  x = (a & M) >> D;
  y = (b & M) >> D;
  return (y > x || (x == 2 && y == 1)) ? 0 : 1;
}

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
  bool M[100];
  M[0] = 1;
  std::fill_n(M + 1, 99, 0);
  // check(0, 1);
  fr(i,0,150) {
    fr(j,0,150) {
      // std::cout << M[j];
      std::cout << check(i, j);
    }
    std::cout << std::endl;
    // fl(j,99,0) {
    //   M[j] = M[j] xor M[j - 1];
    // }
  }
  std::cout << std::endl;
  return 0;
}
