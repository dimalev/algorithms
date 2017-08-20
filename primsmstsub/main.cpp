#include <iostream>
#include <vector>
#include <queue>
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

#ifdef UNITS
void unit_tests() {
  test_header("test units");
}
#endif

struct edge {
  int from, to;
  long length;
};

bool operator<(const edge &left, const edge &right) {
  return left.length > right.length;
}

int main() {
#ifdef UNITS
  unit_tests();
  return 0;
#endif
  int N, M;
  std::cin >> N >> M;
  std::map<int, std::map<int, long>> V;
  fr(i,0,M) {
    int u, v;
    long l;
    std::cin >> u >> v >> l;
    --u; --v;
    auto it = V[u].find(v);
    if(it != V[u].end()) {
      if(it->second < l) {
        it->second = l;
        V[v][u] = l;
      }
    } else {
      V[v][u] = l;
      V[u][v] = l;
    }
  }
  int S;
  std::cin >> S;
  --S;
  std::priority_queue<edge> line;
  int left = N - 1;
  std::vector<bool> filled;
  filled.reserve(N);
  filled[S] = true;
  for(auto &lines : V[S]) {
    int to = lines.first;
    long length = lines.second;
    if(!filled[to]) {
      line.push({S, to, length});
    }
  }
  long res = 0;
  while(line.size() > 0 && left > 0) {
    edge next = line.top();
    TRACE_LINE("study |"
               << (next.from + 1) << " -> "
               << (next.to + 1) << "| = "
               << next.length);
    line.pop();
    if(filled[next.to]) continue;
    filled[next.to] = true;
    for(auto &lines : V[next.to]) {
      int to = lines.first;
      long length = lines.second;
      if(!filled[to]) {
        line.push({next.to, to, length});
      }
    }
    res += next.length;
    --left;
  }
  std::cout << res << std::endl;
  return 0;
}
