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
  int T;
  std::cin >> T;
  while(T--) {
    int N, P, easy = 0, difficult = 0;
    std::cin >> N >> P;
    int P2 = P / 2, P10 = P / 10;
    fr(i,0,N) {
      int D;
      std::cin >> D;
      if(D >= P2) ++easy;
      if(D <= P10) ++difficult;
    }
    std::cout << (easy == 1 && difficult == 2 ? "yes" : "no") << "\n";
  }
  return 0;
}
