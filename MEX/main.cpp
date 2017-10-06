#include <iostream>
#include <vector>

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
    int N, K;
    std::cin >> N >> K;
    int top = N+K+2;
    std::vector<bool> seen(top);
    std::vector<int> BIT(top);
    fr(i,0,N) {
      int v;
      std::cin >> v;
      ++v;
      if(v >= top) continue;
      if(!seen[v]) {
        seen[v] = true;
        while(v < top) {
          ++BIT[v];
          v += v & -v;
        }
      }
    }
    int L = 0, R = top;
    TRACE_LINE(T);
    while(L + 1 < R) {
      int M = (L + R) / 2;
      int sum = 0, it = M;
      while(it > 0) {
        sum += BIT[it];
        it -= it & -it;
      }
      TRACE_LINE("to " << (M-1) << " sum=" << sum);
      if(M - sum <= K) L = M;
      else R = M;
    }
    std::cout << (R-1) << std::endl;
  }
  return 0;
}
