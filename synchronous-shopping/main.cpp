#include <iostream>
#include <algorithm>
#include <queue>
#include <map>

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else

#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)
#define UNIT_TESTS()

#endif

struct Triplet {
  int town, way, fish;
  Triplet(int _town, int _way, int _fish) : town{_town}, way{_way}, fish{_fish} {}
};

void unit_tests() {
}

int main() {
  UNIT_TESTS();
  int N, M, K;
  std::cin >> N >> M >> K;
  int fish[N];
  for(int i = 0; i < N; ++i) {
    int T;
    std::cin >> T;
    fish[i] = 0;
    for(int t = 0; t < T; ++t) {
      int a;
      std::cin >> a;
      fish[i] |= (1 << (a - 1));
    }
    TRACE_LINE("fish " << i << " config = " << fish[i]);
  }
  TRACE_LINE("initializing branches");
  std::map<int, int> branches[N];
  for(int i = 0; i < M; ++i) {
    int u, v, l;
    std::cin >> u >> v >> l;
    --u; --v;
    TRACE_LINE(u << " -> " << v << " = " << l);
    branches[u].emplace(v, l);
    branches[v].emplace(u, l);
  }
  TRACE_LINE("initializing lengths");
  int L[N][1 << K];
  std::queue<Triplet> log;
  for(int i = 0; i < N; ++i) {
    std::fill_n(L[i], 1 << K, 1e8);
  }
  L[0][fish[0]] = 0;
  log.emplace(0, 0, fish[0]);
  TRACE_LINE("starting search");
  while(!log.empty()) {
    Triplet position = log.front();
    log.pop();
    if(L[position.town][position.fish] < position.way) {
      continue;
    }
    TRACE_LINE("visiting " << position.town << " with " << position.fish);
    for(auto branch : branches[position.town]) {
      int next_town = branch.first;
      int path_length = branch.second + position.way;
      int new_fish = position.fish | fish[next_town];
      if(L[next_town][new_fish] > path_length) {
        L[next_town][new_fish] = path_length;
        log.emplace(next_town, path_length, new_fish);
      }
    }
  }
  int result = 2e8;
  for(int i = 0; i < (1 << K); ++i) {
    for(int j = 0; j < (1 << K); ++j) {
      if((i | j) == ((1 << K) - 1)) {
        if(std::max(L[N - 1][i], L[N - 1][j]) < result) {
          result = std::max(L[N - 1][i], L[N - 1][j]);
        }
      }
    }
  }
  std::cout << result << "\n";
  return 0;
}
