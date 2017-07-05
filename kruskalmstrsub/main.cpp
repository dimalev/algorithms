#include <iostream>
#include <algorithm>
#include <tuple>

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

class edge {
  int _u, _v, _w;
 public:
  edge() : _u{0}, _v{0}, _w{0} {}
  edge(int u, int v, int w) : _u{u}, _v{v}, _w{w} {}
  edge(const edge& e) : _u{e._u}, _v{e._v}, _w{e._w} {}
  edge(const edge&& e) : _u{e._u}, _v{e._v}, _w{e._w} {}

  edge& operator=(const edge& other) {
    _u = other._u; _v = other._v; _w = other._w;
    return *this;
  }

  bool operator<(const edge& other) {
    if(_w == other._w)
      return _u + _v + _w < other._u + other._v + other._w;
    return _w < other._w;
  }

  inline int u() const { return _u; }
  inline int v() const { return _v; }
  inline int w() const { return _w; }
};

int prev[3000], size[3000];

int root(int v) {
  if(prev[v] == v) return v;
  prev[v] = prev[prev[v]];
  return root(prev[v]);
}

void join(int v, int u) {
  int vr = root(v);
  int ur = root(u);
  if(vr == ur) return;
  if(size[vr] > size[ur]) {
    prev[ur] = vr;
    size[vr] += size[ur];
  } else {
    prev[vr] = ur;
    size[ur] += size[vr];
  }
}

int main() {
#ifdef UNITS
  unit_tests();
  return 0;
#endif
  edge *edges = new edge[4500000];
  int n, m;
  std::cin >> n >> m;
  for(int i = 0; i < m; ++i) {
    int x, y, r;
    std::cin >> x >> y >> r;
    edges[i] = {x, y, r};
  }
  std::sort(edges, edges + m);
  for(int i = 0; i < n; ++i) {
    prev[i] = i;
    size[i] = 1;
  }
  int total = 0;
  for(int i = 0; i < m; ++i) {
    if(root(edges[i].u()) != root(edges[i].v())) {
      join(edges[i].u(), edges[i].v());
      total += edges[i].w();
    }
  }
  std::cout << total << std::endl;
  return 0;
}
