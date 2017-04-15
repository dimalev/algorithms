#include <iostream>

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else

#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)
#define UNIT_TESTS()

#endif

void unit_tests() {
}

void solve(long test) {
  long n, m, clib, croad;
  std::cin >> n >> m >> clib >> croad;
  if(croad < clib) {
    long colors[n], prev[n], next[n];
    for(long i = 0; i < n; ++i) {
      colors[i] = i;
      prev[i] = -1;
      next[i] = -1;
    }
    long roads = 0;
    for(long i = 0; i < m; ++i) {
      long a, b;
      std::cin >> a >> b;
      --a; --b;
      TRACE_LINE(a << "-" << b << " -> " << colors[a] << " -> " << colors[b]);
      if(colors[a] != colors[b]) {
        ++roads;
        long f = a, l = a;
        colors[a] = colors[b];
        while(next[f] != -1) {
          f = next[f];
          colors[f] = colors[b];
        }
        while(prev[l] != -1) {
          l = prev[l];
          colors[l] = colors[b];
        }
        if(next[b] != -1) {
          next[f] = next[b];
          prev[next[b]] = f;
        }
        next[b] = l;
        prev[l] = b;
      }
    }
    std::cout << (roads * croad + (n - roads) * clib) << "\n";
  } else {
    for(long i = 0; i < m; ++i) {
      long a, b;
      std::cin >> a >> b;
    }
    std::cout << clib * n << "\n";
  }
}

int main() {
  UNIT_TESTS();
  long T;
  std::cin >> T;
  for(long t = 0; t < T; ++t) {
    solve(t);
  }
  return 0;
}
