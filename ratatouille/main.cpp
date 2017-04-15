#include <iostream>
#include <vector>
#include <queue>

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else

#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)
#define UNIT_TESTS()

#endif

constexpr int N_MAX = 10;
constexpr int P_MAX = 10;

class second_greater {
 public:
  bool operator()(const std::pair<int, int> &left,
                  const std::pair<int, int> &right) {
    if(left.second == right.second) {
      return left.first > right.first;
    }
    return left.second > right.second;
  }
};

void solve(int t) {
  int N, P;

  std::cin >> N >> P;

  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, second_greater> ingredients[N];
  int R[N];

  for(int i = 0; i < N; ++i) {
    std::cin >> R[i];
  }

  for(int i = 0; i < N; ++i) {
    int K = R[i];
    for(int j = 0; j < P; ++j) {
      int Q;
      std::cin >> Q;
      int lower = (10 * Q) / (11 * K);
      if((10 * Q) % (11 * R[i]) > 0) ++lower;
      int higher = (10 * Q) / (9 * K);
      if(lower > higher) continue;
      ingredients[i].push(std::make_pair(lower, higher));
    }
  }
  int collected = 0;
  while(true) {
    int lower = 0, higher = 1e6;
    int smallest_second = 1e6, smallest_second_id = -1;
    bool is_empty = false;
    for(int i = 0; i < N; ++i) {
      if(ingredients[i].size() == 0) {
        is_empty = true;
        break;
      }
      lower = std::max(ingredients[i].top().first, lower);
      higher = std::min(ingredients[i].top().second, higher);
      if(ingredients[i].top().second < smallest_second) {
        smallest_second = ingredients[i].top().second;
        smallest_second_id = i;
      }
    }
    if(is_empty) break;
    if(lower <= higher) {
      ++collected;
      for(int i = 0; i < N; ++i) {
        ingredients[i].pop();
      }
    } else {
      ingredients[smallest_second_id].pop();
    }
  }
  std::cout << "Case #" << t << ": " << collected << "\n";
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
