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

int gcd(int a, int b) {
  if(a == 0) return b;
  return gcd(b % a, a);
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
  int N;
  std::cin >> N;
  int a = 1, b = N - 1;
  fr(i,2,N/2+1) {
    if(gcd(i, N - i) == 1 && i * b > a * (N - i)) {
      a = i; b = N - i;
    }
  }
  std::cout << a << " " << b << std::endl;
  return 0;
}
