#include <iostream>
#include <queue>
#include <set>
#include <vector>
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

constexpr int MAX_N = 1e5;

int N, K;

int L[MAX_N], R[MAX_N], C[MAX_N], P[MAX_N], X[MAX_N];

std::map<int, std::vector<int>> children;

long long count(int node, int l, int r) {
  if(l > R[node] || r < L[node]) return 0ll;
  if(l <= L[node] && r >= R[node]) return C[node];
  long long res = node >= l && node <= r ? 1ll : 0ll;
  for(int child : children[node]) {
    res += count(child, l, r);
  }
  return res;
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
  std::cin >> N >> K;
  fr(i,0,N) P[i] = i;
  fr(i,0,N-1) {
    int u, v;
    std::cin >> u >> v;
    --u; --v;
    children[u].push_back(v);
    ++X[u];
    P[v] = u;
  }
  std::queue<int> leafs;
  fr(i,0,N) {
    L[i] = i; R[i] = i; C[i] = 1;
    if(X[i] == 0) leafs.push(i);
  }
  while(!leafs.empty()) {
    int node = leafs.front();
    leafs.pop();
    TRACE(node+1);
    if((--X[P[node]]) == 0) leafs.push(P[node]);
    for(int child : children[node]) {
      TRACE(" " << (child+1));
      L[node] = std::min(L[node], L[child]);
      R[node] = std::max(R[node], R[child]);
      C[node] += C[child];
    }
    TRACE_LINE("");
  }
  long long res = 0ll;
  fr(n,0,N) {
    long long c = count(n, n - K, n + K) - 1ll;
    TRACE_LINE((n+1) << ": " << (L[n]+1) << "-" << (R[n]+1) << " " << C[n] << " c=" << c);
    res += c;
  }
  std::cout << res << std::endl;
  return 0;
}
