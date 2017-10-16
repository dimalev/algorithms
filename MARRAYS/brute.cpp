#include <iostream>
#include <limits>
#include <algorithm>
#include <vector>
#include <map>

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else
#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)
#endif

#define fr(v,s,e) for(long long v = s; v < e; ++v)
#define fl(v,s,e) for(long long v = s; v > e; --v)

int main() {
  int T;
  std::cin >> T;
  while(T--) {
    int N;
    std::cin >> N;
    std::vector<std::vector<long long>> A(N);
    fr(i,0,N) {
      int s;
      std::cin >> s;
      A[i].resize(s);
      fr(j,0,s) {
        std::cin >> A[i][j];
      }
    }
    std::vector<std::pair<long long, long long>> best(2);
    long long min = std::numeric_limits<long long>::max(), max = 0l;
    fr(i,0,A[0].size()) {
      min = std::min(min, A[0][i]);
      max = std::max(max, A[0][i]);
    }
    best[0] = std::make_pair(min, 0);
    best[1] = std::make_pair(max, 0);
    long long the_best = 0;
    fr(i,1,N) {
      TRACE_LINE("== " << i);
      // std::vector<std::pair<long long, long long>> next_best(A[i].size());
      std::map<long long, long long> next_best;
      fr(j,0,A[i].size()) {
        int j1 = (j + A[i].size() - 1) % A[i].size();
        long long max = 0;
        if(i == 1) {
          long long left = std::abs(best.begin()->first - A[i][j]),
            right = std::abs(best.rbegin()->first - A[i][j]);
          max = std::max(left, right);
        } else {
          fr(k,0,best.size()) {
            long long candidate =
              best[k].second + std::abs(best[k].first - A[i][j]) * i;
            max = std::max(max, candidate);
          }
        }
        TRACE_LINE(A[i][j] << " -> " << A[i][j1] << ": " << max);
        if(i == N-1) the_best = std::max(the_best, max);
        else {
          next_best[A[i][j1]] = std::max(next_best[A[i][j1]], max);
        }
      }
      if(i != N-1) {
        best.clear();
        for(const auto &p : next_best) {
          best.emplace_back(p.first, p.second);
        }
      }
    }
    std::cout << the_best << "\n";
  }
}
