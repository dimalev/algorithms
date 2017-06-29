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


using edge = std::tuple<int, int, int>;

inline int comp(edge l, edge r) {
	if(std::get<2>(l) == std::get<2>(r))
		return std::get<0>(l) + std::get<1>(l) + std::get<2>(l) < std::get<0>(r) + std::get<1>(r) + std::get<2>(r);
	return std::get<2>(l) < std::get<2>(r);
}

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
	std::sort(edges, edges + m, comp);
	for(int i = 0; i < n; ++i) {
		prev[i] = i;
		size[i] = 1;
	}
	int total = 0;
	for(int i = 0; i < m; ++i) {
		int u, v, w;
		std::tie(u, v, w) = edges[i];
		if(root(u) != root(v)) {
			join(u, v);
			total += w;
		}
	}
	std::cout << total << std::endl;
  return 0;
}
