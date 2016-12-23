#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else

#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)
#define UNIT_TESTS()

#endif

int C(int N, nint k) {
  long long res = 1;
  for(long long i = N - k + 1; i <= N; ++i) res *= i;
  for(long long i = 1; i <= k; ++i) res /= i;
  return res;
}

void unit_tests() {
}

int main() {
  UNIT_TESTS();
  int N;
  std::map<int, int> L;
  std::cin >> N;
  for(int i = 0; i < N; ++i) {
    int l;
    std::cin >> l;
    std::pair<std::map<int, int>::iterator, bool> place = L.emplace(l, 0);
    place.first->second++;
  }
  long count = 0;
  auto longest = L.rbegin();
  while(longest != L.rend()) {
    ++longest;
    int l = longest->first;
    int lc = longest->second;
    if(lc >= 2) {
      auto left = L.begin();
      auto right = prev(L.find(l));
      std::vector<int> variations;
      int clc2 = C(lc, 2);
      while(left != right) {
        int m = right->first;
        int mc = right->second;
        int s = left->first;
        int sc = left->second;
        if(m + s > l) --right;
        else if(m + s < l) ++left;
        else {
          variations.push_back(mc * sc);
          if(mc >= 2 && sc >= 2) count += C(mc, 2) * C(sc, 2) * clc2;
          --right;
          if(right == left) break;
          ++left;
        }
      }
      if(2 * right->first == l && right->second >= 2) {
        variations.push_back(C(right->second, 2));
        if(right->second >= 4)
          count += clc2 * C(right->second, 4);
      }
      int sum = 0;
      for(int v : variations) sum += v;
      for(int v : variations) {
        sum -= v;
        count += clc2 * v * sum;
      }
      if(lc >= 3) {
        int clc3 = C(lc, 3);
        auto small_it = L.begin();
        int l3 = l / 3;
        while(small_it->first <= l3) {
          if(3 * small_it->first == l && small_it->second >= 3)
            count += clc3 * C(small_it->second, 3);
          
        }
      }
    }
  }
  return 0;
}
