#include <iostream>
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

class pair_greater_by_first {
 private:
  std::greater<long> my_greater;
 public:
  bool operator()(const std::pair<long, long> &left,
                  const std::pair<long, long> &right) {
    return my_greater(left.first, right.first);
  }
};

void solve(int t) {
  long N, K;
  std::cin >> N >> K;
  TRACE_LINE(":: " << N << ", " << K << " ::");
  std::map<long, long, std::greater<long>> pieces;
  pieces.emplace(N, 1);
  while(true) {
    std::pair<long, long> biggest_pair = *pieces.begin();
    long length = biggest_pair.first;
    long count = biggest_pair.second;
    long left = (length - 1) / 2;
    long right = (length - 1) - left;
    TRACE_LINE(length << ": " << count << " (" << K << ")");
    if(count >= K) {
      std::cout << "Case #" << t << ": " << right << " " << left << "\n";
      return;
    }
    pieces.erase(length);
    auto left_it = pieces.find(left);
    if(left_it == pieces.end()) {
      pieces.emplace(left, count);
    } else left_it->second += count;
    auto right_it = pieces.find(right);
    if(right_it == pieces.end()) {
      pieces.emplace(right, count);
    } else right_it->second += count;
    K -= count;
  }
}

void solve_greedy(int t) {
  long N, K;
  std::cin >> N >> K;
  std::vector<bool> occupied(N);
  std::fill(occupied.begin(), occupied.end(), false);
  int cmin = -1;
  int cmax = -1;
  int pos = -1;
  for(int i = 0; i < K; ++i) {
    cmin = -1;
    cmax = -1;
    pos = -1;
    for(int j = 0; j < N; ++j) {
      if(!occupied[j]) {
        int left = 0;
        int right = 0;
        while(left < j && !occupied[j - left - 1]) ++left;
        while(right + j + 1 < N && !occupied[j + right + 1]) ++right;
        int mmin = std::min(left, right);
        int mmax = std::max(left, right);
        bool is_better = false;
        if(mmin > cmin) {
          is_better = true;
        } else if(mmin == cmin) {
          if(mmax > cmax) {
            is_better = true;
          }
        }
        if(is_better) {
          cmin = mmin;
          cmax = mmax;
          pos = j;
        }
      }
    }
    // TRACE_LINE("-- " << i << ": " << pos);
    occupied[pos] = true;
  }
  std::cout << "Case #" << t << ": " << cmax << " " << cmin << "\n";
}

void unit_tests() {
  std::map<long, long, std::greater<long>> pieces;
  pieces.emplace(1234, 23);
  pieces.emplace(4444, 12);
  pieces.emplace(122, 10000);
  long biggest = pieces.begin()->first;
  std::cout << biggest << ": " << pieces[biggest] << "\n";
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
