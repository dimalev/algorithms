#include <iostream>
#include <set>
#include <queue>

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else

#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)
#define UNIT_TESTS()

#endif

void unit_tests() {
}

constexpr int MAX_N = 3 * 1e5;

int N;

std::set<int> P[MAX_N];
int C_proto[MAX_N];

void solve(int q) {
  std::queue<int> line;
  static int C[MAX_N], colors[MAX_N], res[MAX_N];
  for(int i = 0; i < N; ++i) {
    res[i] = 0;
    colors[i] = 0;
    C[i] = C_proto[i];
    if(C[i] == 1) line.push(i);
  }
  int B;
  std::cin >> B;
  for(int b = 0; b < B; ++b) {
    int v;
    std::cin >> v;
    --v;
    colors[v] = 1;
  }
  // TRACE_LINE("--");
  while(!line.empty()) {
    int v = line.front();
    // TRACE_LINE(v + 1);
    line.pop();
    for(int u : P[v]) {
      if(C[u] == 1 && u != 0) {
        colors[v] += colors[u];
      } else {
        --C[u];
        if((C[u] == 1 && u != 0) || (u == 0 && C[u] == 0)) {
          line.push(u);
        }
      }
      // TRACE_LINE((u + 1) << ": " << C[u]);
    }
    ++res[colors[v]];
  }
  for(int i = 0; i <= B; ++i) {
    std::cout << (i == 0 ? "" : " ") << res[i];
  }
  std::cout << "\n";
}

int main() {
  UNIT_TESTS();
  std::cin >> N;
  for(int i = 0; i < N - 1; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u; --v;
    ++C_proto[u]; ++C_proto[v];
    P[u].insert(v);
    P[v].insert(u);
  }
  int Q;
  std::cin >> Q;
  for(int q = 0; q < Q; ++q) {
    solve(q);
  }
  return 0;
}
