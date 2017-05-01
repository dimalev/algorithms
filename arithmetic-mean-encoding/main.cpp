#include <iostream>
#include <algorithm>

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else

#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)
#define UNIT_TESTS()

#endif

int count_ones(long V) {
  int ones = 0;
  while(V > 0) {
    if(V % 2 == 1) {
      ++ones;
    }
    V /= 2;
  }
  return ones;
}

void solve(int t) {
  long N;
  std::cin >> N;
  for(long k = 1; k < 8192; ++k) {
    int ones = count_ones(N * k);
    if(ones == k) {
      long V = k * N;
      std::cout << k;
      int p = 0;
      while(V > 0) {
        if(V % 2 == 1) {
          std::cout << " " << p;
        }
        ++p;
        V /= 2;
      }
      std::cout << "\n";
      return;
    } else if(ones < k) {
      int hysto[65], p = 0;
      std::fill_n(hysto, 65, 0);
      long V = N * k;
      while(V > 0) {
        if(V % 2 == 1) {
          hysto[p] = 1;
        }
        ++p;
        V /= 2;
      }
      int lk = k - ones;
      while(lk > 0 && p > 0) {
        if(hysto[p] > 0) {
          if(lk > hysto[p]) {
            hysto[p - 1] += 2 * hysto[p];
            lk -= hysto[p];
            hysto[p] = 0;
          } else {
            hysto[p] -= lk;
            hysto[p - 1] += 2 * lk;
            lk = 0;
          }
        }
        --p;
      }
      if(lk == 0) {
        std::cout << k;
        for(p = 64; p >=0; --p) {
          for(int c = 0; c < hysto[p]; ++c) {
            std::cout << " " << p;
          }
        }
        std::cout << "\n";
        return;
      }
    }
  }
}

void unit_tests() {
}

int main() {
  UNIT_TESTS();
  int T;
  std::cin >> T;
  for(int t = 1; t <= T; ++t) {
    solve(t);
  }
  return 0;
}
