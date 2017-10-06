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

int main() {
#ifdef UNITS
  unit_tests();
  return 0;
#endif
  int N, M;
  std::cin >> N >> M;
  int BIT[N+1];
  std::fill_n(BIT, N+1, 0);
  fr(i,0,M) {
    int c;
    std::cin >> c;
    if(c == 1) {
      int u, v;
      std::cin >> u >> v;
      int c = u;
      while(c <= N) {
        BIT[c] += 1;
        c += c & (-c);
      }
      c = v+1;
      while(c <= N) {
        BIT[c] -= 1;
        c += c & (-c);
      }
    } else {
      int ind;
      std::cin >> ind;
      int c = ind;
      int x = 0, xc = 0;
      while(c > 0) {
        x += BIT[c];
        c -= c & (-c);
      }
      c = ind - 1;
      while(c > 0) {
        xc += BIT[c];
        c -= c & (-c);
      }
      std::cout << (x>0?"yes":"no") << "\n";
    }
  }
  return 0;
}
