#include <iostream>
#include <queue>
#include <limits>
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

class edge {
 public:
  edge(int d, int l) : destination{d}, length{l} {}
  int destination;
  int length;
};
bool operator<(const edge &left, const edge &right) {
  return left.length > right.length;
}

#ifdef UNITS
void unit_tests() {
  test_header("test units");
}
#endif

void solve() {
  int N, M, S;
  std::cin >> N >> M;
  int d[N], left = N - 1;
  std::fill_n(d, N, std::numeric_limits<int>::max());
  std::map<int, int> edges[N];
  fr(i, 0, M) {
    int s, e, l;
    std::cin >> s >> e >> l;
    --s; --e;
    if(edges[s][e] == 0 || edges[s][e] > l) {
      edges[s][e] = l;
      edges[e][s] = l;
    }
  }
  std::cin >> S;
  --S;
  d[S] = 0;
  std::priority_queue<edge> nodes;
  for(auto pair : edges[S]) {
    nodes.emplace(pair.first, pair.second);
  }
  while(!nodes.empty()) {
    auto node = nodes.top();
    nodes.pop();
    if(node.length < d[node.destination]) {
      d[node.destination] = node.length;
      if(--left == 0) break;
      for(auto pair : edges[node.destination])
        if(node.length + pair.second < d[pair.first])
          nodes.emplace(pair.first, node.length + pair.second);
    }
  }
  bool isFirst = true;
  fr(i,0,N) {
    if(S != i) {
      if(!isFirst) std::cout << " ";
      std::cout << (d[i] == std::numeric_limits<int>::max() ? -1 : d[i]);
      isFirst = false;
    }
  }
  std::cout << std::endl;
}

int main() {
#ifdef UNITS
  unit_tests();
  return 0;
#endif
  int T;
  std::cin >> T;
  fr(t,0,T) solve();
  return 0;
}
