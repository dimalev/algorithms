#include <iostream>
#include <queue>
#include <limits>
#include <map>
#include <tuple>

#define fr(v,s,e) for(int v = s; v < e; ++v)
#define fl(v,s,e) for(int v = s; v > e; --v)

using pipe_config = std::map<int, std::map<int, int>>;

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

std::tuple<int, pipe_config> max_flow(pipe_config &pipes, int N) {
  int flow[N], best = 0;
  pipe_config setup;
  for(;;) {
    std::fill_n(flow, N, -1);
    flow[0] = std::numeric_limits<int>::max();
    std::queue<int> nodes;
    nodes.push(0);
    while(!nodes.empty() && flow[N - 1] == -1) {
      int source = nodes.front();
      nodes.pop();
      for(auto next : pipes[source]) {
        if(flow[next.first] == -1 && next.second > setup[next.first][source]) {
          flow[next.first] = source;
          nodes.push(next.first);
        }
      }
      for(auto next : setup[source]) {
        if(flow[next.first] == -1 && next.second > 0) {
          flow[next.first] = source;
          nodes.push(next.first);
        }
      }
    }
    if(flow[N - 1] == -1) break;
    int node = N - 1;
    int weight = std::numeric_limits<int>::max();
    while(node != 0) {
      int next_node = flow[node];
      int next_weight = pipes[next_node][node] > 0
        ? pipes[next_node][node] - setup[node][next_node]
        : setup[next_node][node];
      weight = std::min(weight, next_weight);
      node = next_node;
    }
    node = N - 1;
    TRACE(weight << ":");
    while(node != 0) {
      int next_node = flow[node];
      TRACE(" " << next_node);
      if(pipes[next_node][node] > 0) {
        setup[node][next_node] += weight;
      } else {
        setup[next_node][node] -= weight;
      }
      node = next_node;
    }
    TRACE_LINE("");
    best += weight;
  }
  return std::make_tuple(best, setup);
}

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
  pipe_config pipes;
  fr(i,0,M) {
    int u, v, p;
    std::cin >> u >> v >> p;
    pipes[u][v] = p;
  }
  int value;
  pipe_config setup;
  std::tie(value, setup) =
    max_flow(pipes, N);
  std::cout << value << std::endl;
  return 0;
}
