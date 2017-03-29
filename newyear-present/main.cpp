#include <iostream>
#include <algorithm>
#include <map>
#include <set>

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else

#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)
#define UNIT_TESTS()

#endif

constexpr int64_t MAX_N = 3000;
constexpr int64_t MAX_L = 1e7;

int64_t C(const int64_t &n, const int64_t &k) {
  int64_t res = 1;
  for(int64_t i = n - k + 1; i <= n; ++i) res *= i;
  for(int64_t i = 2; i <= k; ++i) res /= i;
  return res;
}

void unit_tests() {
}

int main() {
  UNIT_TESTS();
  int64_t N;
  std::set<int64_t> L;
  std::map<int64_t, int64_t> C;
  std::cin >> N;
  for(int i = 0; i < N; ++i) {
    int64_t l;
    std::cin >> l;
    auto Cl = C.find(l);
    if(Cl == C.end()) {
      C.insert(std::make_pair(l, 1));
      L.insert(l);
    } else {
      ++Cl->second;
    }
  }

  auto Cstart = C.begin();
  int64_t total;
  for(auto Cl = Cstart; Cl != C.end(); Cl++) {
    int64_t l = Cl->first;
    int64_t c = Cl->second;
    int64_t total_for_l = 0;
    if(c >= 3) {
      int64_t combs = count3(l, Cstart, Cl) * C(c, 3);
      total_for_l += combs;
    }
    if(c >= 2) {
      int64_t combs = count2x2(l, Cstart, Cl) * C(c, 2);
      total_for_l += combs;
    }
    total += total_for_l;
  }
  std::cout << total;
  return 0;
}
