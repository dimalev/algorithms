#include <iostream>
#include <string>
#include <sstream>
#include <tuple>
#include <cmath>
#include <limits>
#include <algorithm>
#include <queue>
#include <vector>
#include <set>

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

using ll = long long;

class node_t {
public:
  int level, parent, parent2;
  ll cost, cost2;
  std::vector<std::pair<int, ll>> connections;
  std::string str() {
    std::stringstream ss;
    ss << "(" << parent << "," << cost << ");("
       << parent2 << "," << cost2 << ")[" << level << "]";
    return ss.str();
  }
};

class tree {
public:
  explicit tree(int size) : size{size} {
    nodes.resize(size);
  }

  void edge(int u, int v, long long c) {
    nodes[u].connections.emplace_back(v, c);
    nodes[v].connections.emplace_back(u, c);
  }

  void build() {
    int root = 0;
    nodes[root].parent = root;
    nodes[root].parent2 = root;
    nodes[root].cost2 = 0ll;
    std::queue<int> line;
    line.push(root);
    std::vector<bool> visits(size);
    int max_level = 0;
    int it = 0;
    while(!line.empty()) {
      int current = line.front();
      int level = nodes[current].level + 1;
      int parent = nodes[current].parent;
      if(max_level < level) max_level = level;
      line.pop();
      for(const auto &edge : nodes[current].connections) {
        int next = edge.first;
        if(next == parent) continue;
        ll cost = edge.second;
        nodes[next].parent = current;
        nodes[next].cost = cost;
        nodes[next].level = level;
        if(nodes[next].connections.size() > 1) line.push(next);
      }
    }
    line.push(root);
    int step = std::max(4, (int)round(sqrt(max_level)));
    while(!line.empty()) {
      int current = line.front();
      int parent = nodes[current].parent;
      int parent2 = nodes[current].parent2;
      int level2 = nodes[parent2].level;
      int cost2 = nodes[current].cost2;
      for(const auto &edge : nodes[current].connections) {
        int next = edge.first;
        if(next == parent) continue;
        TRACE_LINE(current << "->" << next << " "
                   << parent2 << " " << cost2 << " " << level2 << " "
                   << parent << " " << nodes[current].cost << " " << nodes[current].level);
        ll cost = edge.second;
        if(nodes[next].level - level2 > step) {
          nodes[next].parent2 = current;
          nodes[next].cost2 = cost;
        } else {
          nodes[next].parent2 = parent2;
          nodes[next].cost2 = cost2 + cost;
        }
        if(nodes[next].connections.size() > 1) line.push(next);
      }
      line.pop();
    }
  }

  std::tuple<int, ll> path(int u, int v) {
    ll costu = 0ll, costv = 0ll;
    TRACE(u << " " << v << " ");
    while(u != v) {
      int u2 = nodes[u].parent2;
      int v2 = nodes[v].parent2;
      if(u2 != v2) {
        if(nodes[u2].level < nodes[v2].level) {
          costv += nodes[v].cost2;
          v = v2;
        } else if(nodes[u2].level > nodes[v2].level) {
          costu += nodes[u].cost2;
          u = u2;
        } else {
          costv += nodes[v].cost2;
          costu += nodes[u].cost2;
          v = v2;
          u = u2;
        }
      } else {
        if(nodes[u].level < nodes[v].level) {
          costv += nodes[v].cost;
          v = nodes[v].parent;
        } else if(nodes[u].level > nodes[v].level) {
          costu += nodes[u].cost;
          u = nodes[u].parent;
        } else {
          costv += nodes[v].cost;
          costu += nodes[u].cost;
          v = nodes[v].parent;
          u = nodes[u].parent;
        }
      }
    }
    TRACE_LINE(u);
    return {u, costu + costv};
  }

  std::string str() {
    std::stringstream ss;
    std::set<int> line;
    line.insert(0);
    int level = 0;
    while(!line.empty()) {
      std::set<int> next_nodes;
      ss << level++ << ":\t";
      for(int node_id : line) {
        node_t &node = nodes[node_id];
        ss << node_id << ":" << node.str() << " ";
        for(const auto &edge : node.connections) {
          if(edge.first != node.parent) {
            next_nodes.emplace(edge.first);
          }
        }
      }
      line = std::move(next_nodes);
      ss << "\n";
    }
    return ss.str();
  }

  std::vector<node_t> nodes;
  int size;
};

#ifdef UNITS
void unit_tests() {
  test_header("tree");
  int N;
  std::cin >> N;
  tree test(N);
  fr(i,0,N-1) {
    int u, v;
    ll c;
    std::cin >> u >> v >> c;
    test.edge(u, v, c);
  }
  test.build();
  TRACE_LINE(test.str());
  int M;
  std::cin >> M;
  fr(i,0,M) {
    int u, v;
    std::cin >> u >> v;
    int p;
    ll c;
    std::tie(p, c) = test.path(u, v);
    std::cout << p << " " << c << "\n";
  }
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
    int N;
    std::cin >> N;
    tree trees[] = {tree(N), tree(N)};
    fr(k,0,2) {
      fr(i,0,N-1) {
        int u, v;
        ll c;
        std::cin >> u >> v >> c;
        --u; --v;
        TRACE_LINE(u << " " << v);
        trees[k].edge(u, v, c);
      }
      trees[k].build();
    }
    ll sum = 0ll;
    fr(i,0,N-1) {
      fr(j,i+1,N) {
        int p1, p2;
        ll c1, c2;
        std::tie(p1, c1) = trees[0].path(i,j);
        std::tie(p2, c2) = trees[1].path(i,j);
        sum += std::min(c1, c2);
      }
    }
    std::cout << sum << std::endl;
  }
  return 0;
}
