#include <iostream>
#include <vector>
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

class biggest {
public:
  void put(int max, int source) {
    if(max > max2) {
      if(max > max1) {
        max2 = max1;
        max1 = max;
        max_source = source;
        return;
      }
      max2 = max;
    }
  }

  int max(int but_not) const {
    if(but_not == max_source) return max2;
    return max1;
  }
  int max1, max2, max_source;
};

struct edge_details {
  int children, cut;
};

int N, N2;
std::vector<std::map<int, edge_details>> connections;
std::vector<biggest> maxes;
std::vector<bool> is_reparent_used, good;

#ifdef UNITS
void unit_tests() {
  test_header("test units");
}
#endif

int dfs(int current, int parent) {
  int children = 0;
  for(auto &edge : connections[current]) {
    if(edge.first != parent) {
      int current_children = dfs(edge.first, current);
      TRACE_LINE(current << " -> " << edge.first << ": " << current_children);
      edge.second.children = current_children;
      children += current_children;
      if(current_children <= N2) {
        int bigmax = std::max(current_children, edge.second.cut);
        maxes[current].put(bigmax, edge.first);
      } else {
        maxes[current].put(edge.second.cut, edge.first);
        if(is_reparent_used[current]) {
          good[current] = false;
        } else if(current_children - edge.second.cut > N2) {
          good[current] = false;
        } else {
          is_reparent_used[current] = true;
        }
      }
    }
  }
  if(parent != current) {
    connections[parent][current].cut = maxes[current].max(-2);
    connections[current][parent].children = N - children - 1;
  }
  return children + 1;
}

void dfs2(int current, int parent) {
  int max = maxes[parent].max(current);
  connections[current][parent].cut = max;
  if(connections[current][parent].children > N2) {
    if(connections[current][parent].children - max > N2) {
      good[current] = false;
    } else if(is_reparent_used[current]) {
      good[current] = false;
    } else {
      is_reparent_used[current] = true;
    }
    connections[current][parent].cut = max;
  } else {
    connections[current][parent].cut = std::max(
        max,
        connections[current][parent].children
    );
  }
  maxes[current].put(connections[current][parent].cut, parent);
  for(auto &edge : connections[current]) {
    if(edge.first != parent) {
      dfs2(edge.first, current);
    }
  }
}

int main() {
#ifdef UNITS
  unit_tests();
  return 0;
#endif
  std::cin >> N;
  N2 = N / 2;
  connections.resize(N);
  is_reparent_used.resize(N);
  maxes.resize(N);
  good.resize(N);
  std::fill(good.begin(), good.end(), true);
  fr(i,0,N-1) {
    int u, v;
    std::cin >> u >> v;
    --u; --v;
    connections[u][v] = {0, 0};
    connections[v][u] = {0, 0};
  }
  dfs(0,0);
  for(auto &edge : connections[0]) {
    bool is_reparent_used = false;
    dfs2(edge.first, 0);
    if(good[0] && edge.second.children > N2) {
      if(is_reparent_used) {
        good[0] = false;
      } else {
        is_reparent_used = true;
        if(edge.second.children - edge.second.cut > N2) {
          good[0] = false;
        }
      }
    }
  }
  for(int i = 0;  i < N; ++i) {
    if(i > 0) std::cout << " ";
    std::cout << (good[i] ? '1' : '0');
  }
  std::cout << std::endl;
  return 0;
}
