#include <iostream>
#include <functional>
#include <queue>
#include <vector>
#include <limits>
#include <algorithm>
#include <map>

#define fr(v,s,e) for(int v = s; v < e; ++v)
#define fl(v,s,e) for(int v = s; v > e; --v)

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

constexpr int maxi = std::numeric_limits<int>::max();

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
  int N, M;
  std::cin >> N >> M;
  std::map<int, std::map<int, int>> E;
  fr(i,0,M) {
    int u, v, c;
    std::cin >> u >> v >> c;
    if(E[u][v] == 0 || E[u][v] > c) E[u][v] = c;
    if(E[v][u] == 0 || E[v][u] > c) E[v][u] = c;
  }
  int minFare[N+1];
  std::fill_n(minFare, N+1, maxi);
  minFare[1] = 0;
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> Q;
  Q.emplace(0, 1);
  while(!Q.empty()) {
    auto pair = Q.top();
    Q.pop();
    int cost = pair.first;
    int u = pair.second;
    TRACE_LINE(cost << " " << u);
    if(cost > minFare[u]) continue;
    minFare[u] = cost;
    for(auto &edge : E[u]) {
      int v = edge.first;
      int c = std::max(cost, edge.second);
      if(minFare[v] == maxi) {
        Q.emplace(c, v);
      }
    }
  }
  if(minFare[N] == std::numeric_limits<int>::max()) {
    std::cout << "NO PATH EXISTS" << std::endl;
    return 0;
  }
  std::cout << minFare[N] << std::endl;
  return 0;
}
