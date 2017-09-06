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
  long n, k;
  std::cin >> n >> k;
  if(n == k) std::cout << "0 0\n";
  else {
    std::cout << std::min(1l, k) << " ";
    long x1 = (n - k) / 2;
    if(x1 > k) x1 = k;
    long x2 = (n - k) % 2;
    if(x2 > k - x1) x2 = k -x1;
    long x3 = n - 3 * x1 - 2 * x2;
    if(x3 > k - x1 - x2) x3 = k - x1 - x2;
    std::cout << (2 * x1 + x2) << std::endl;
  }
  return 0;
}
