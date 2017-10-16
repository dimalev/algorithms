#include <iostream>
#include <algorithm>
#include <vector>

#define fr(v,s,e) for(int v = s; v < e; ++v)
#define fl(v,s,e) for(int v = s; v > e; --v)

using ll = long long;

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
  fr(t,0,T) {
    int N, K;
    std::cin >> N >> K;
    std::vector<std::pair<int, int>> pivots;
    fr(i,0,K) {
      int p, q;
      std::cin >> p >> q;
      --p;
      pivots.emplace_back(p, q);
    }
    std::sort(pivots.begin(), pivots.end());
    ll res = N;
    TRACE_LINE("----- " << N);
    int l = 0;
    fr(i,1,N-1) {
      if(l < K) {
        if(pivots[l].first > i) {
          ll count = std::min(i, pivots[l].first - i - 1);
          TRACE_LINE(i << " " << count);
          res += count;
        } else if(pivots[l].first == i) {
          if(l + 1 < K) {
            ll count = std::min(i, pivots[l + 1].first - i - 1);
            TRACE_LINE(i << " " << count);
            res += count;
          } else {
            ll count = std::min(i, N - i - 1);
            TRACE_LINE(i << " " << count);
            res += count;
          }
        } else {
          int R = l + 1;
          while(R < K && pivots[R].first <= i) ++R;
          int L = l;
          TRACE_LINE(i << ": " << L << "->" << R);
          while(R < K && L >= 0 && pivots[L].second == pivots[R].second) {
            --L; ++R;
          }
          if(R >= K && L < 0) {
            ll count = std::min(i, N - i - 1);
            TRACE_LINE(i << " " << count);
            res += count;
          } else if(R >= K) {
            ll count = std::min(i - pivots[L].first - 1, N - i - 1);
            TRACE_LINE(i << " " << count);
            res += count;
          } else if(L < 0) {
            ll count = std::min(i, pivots[R].first - i - 1);
            TRACE_LINE(i << " " << count);
            res += count;
          } else {
            ll count = std::min(i - pivots[L].first - 1, pivots[R].first - i - 1);
            TRACE_LINE(i << " " << count);
            res += count;
          }
        }
        if(l + 1 < K && pivots[l + 1].first <= i) {
          ++l;
        }
      } else {
        ll count = std::min(i, N - i - 1);
        TRACE_LINE(i << " " << count);
        res += count;
      }
    }
    std::cout << res << std::endl;
  }
  return 0;
}
