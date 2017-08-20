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
  int N, D;
  std::cin >> N >> D;
  unsigned char C[200];
  std::fill_n(C, 200, 0);
  unsigned char V[N];
  fr(i,0,D) {
    int c;
    std::cin >> c;
    C[c]++;
    V[i] = c;
  }
  int res = 0;
  fr(i,D,N) {
    int c;
    std::cin >> c;
    V[i] = c;
    int d1, d2;
    int t = 0;
    fr(k,0,200) {
      if(C[k] > 0) {
        TRACE_LINE("-- " << k << ": " << (int)C[k]);
        t += C[k];
        if(t >= D / 2) {
          d1 = k;
          if(t >= D / 2 + 1) {
            d2 = k;
          } else {
            fr(p,k + 1, 200) {
              if(C[p] != 0) {
                TRACE_LINE("-- " << p << ": " << (int)C[p]);
                d2 = p;
                break;
              }
            }
          }
          break;
        }
      }
    }
    TRACE_LINE(c << " vs " << d1 << " " << d2);
    C[V[i - D]]--;
    C[c]++;
    if(D % 2 == 1) {
      if(c >= 2 * d2) {
        ++res;
      }
    } else {
      if(c >= d1 + d2) {
        ++res;
      }
    }
  }
  std::cout << res << std::endl;
  return 0;
}
