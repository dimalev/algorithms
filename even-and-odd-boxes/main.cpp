#include <iostream>

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
  int n;
  std::cin >> n;
  int C[100000];
  int extra = 0;
  int both = 0;
  int even = 0;
  for(int i = 0; i < n; ++i) {
    int a;
    std::cin >> a;
    if(a % 2 == i % 2) {
      if(a > 2) even += (a - 1) / 2;
    } else {
      if(a > 1) {
        ++both;
        if (a > 2) {
          even += (a - 1) / 2 - 1;
        }
      } else {
        ++extra;
      }
    }
  }
  TRACE_LINE("evens: " << even);
  TRACE_LINE("both: " << both);
  TRACE_LINE("extra: " << extra);
  int used = 0;
  if(extra > both) {
    extra -= both;
    if(extra % 2 == 1 || extra > even * 2) {
      std::cout << "-1\n";
    } else {
      std::cout << (both + extra) << "\n";
    }
  } else {
    both -= extra;
    if(both % 2 == 1) {
      std::cout << "-1\n";
    } else {
      std::cout << (both / 2 + extra) << "\n";
    }
  }
}

int main() {
#ifdef UNITS
  unit_tests();
  return 0;
#endif
  int q;
  std::cin >> q;
  for(int i = 0; i < q; ++i) solve(i);
  return 0;
}
