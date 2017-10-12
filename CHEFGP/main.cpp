#include <iostream>
#include <cassert>

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

constexpr int MAXN = 1e5;

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
  char s[MAXN + 1];
  while(T--) {
    int x, y, a = 0, b = 0;
    std::cin >> s;
    std::cin >> x >> y;
    for(int i = 0; s[i]; ++i) {
      if(s[i] == 'a') ++a;
      else if(s[i] == 'b') ++b;
      else assert(false);
    }
    int ia = 0, ib = 0;
    while(a > 0 || b > 0) {
      int ba = (a + ia) / x + std::min((a + ia) % x, 1);
      int bb = (b + ib) / y + std::min((b + ib) % y, 1);
      if(a > 0 && ba > bb) {
        if(ia < x) {
          int d = std::min(a,x-ia);
          fr(i,0,d) {
            std::cout << 'a';
          }
          a -= d;
          ia += d;
          ib = 0;
        } else if(b > 0) {
          ia = 0;
          int d = std::min(y, std::min(b, std::max(b / ba, 1)));
          fr(i,0,d) {
            std::cout << 'b';
          }
          b -= d;
          ib += d;
          ia = 0;
        } else {
          std::cout << '*';
          ia = 0;
          ib = 0;
        }
      } else {
        if(ib < y && b > 0) {
          int d = std::min(b,y-ib);
          fr(i,0,d) {
            std::cout << 'b';
          }
          b -= d;
          ib += d;
          ia = 0;
        } else if(a > 0) {
          ib = 0;
          int d = std::min(x, std::min(a, std::max(a / bb, 1)));
          fr(i,0,d) {
            std::cout << 'a';
          }
          a -= d;
          ia += d;
          ib = 0;
        } else {
          std::cout << '*';
          ia = 0;
          ib = 0;
        }
      }
    }
    std::cout << "\n";
  }
  return 0;
}
