#include <iostream>
#include <iomanip>
#include <algorithm>
#include <queue>
#include <map>
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

constexpr long long base = 0b10000000000000000000000000000000000000000000000000000000000000 - 1;

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
  int N, Q;
  std::cin >> N >> Q;
  std::map<int, std::set<int>> E;
  fr(i,0,N-1) {
    int u, v;
    std::cin >> u >> v;
    E[u].insert(v);
    E[v].insert(u);
  }
  std::queue<int> next;
  int D[N];
  std::fill_n(D, N, -1);
  D[0] = 0;
  next.push(0);
  while(!next.empty()) {
    int r = next.front();
    next.pop();
    for(const auto &v : E[r]) {
      if(D[v] == -1) {
        D[v] = D[r] + 1;
        next.push(v);
      }
    }
  }
  long long max_depth = (long long)*std::max_element(D, D + N);
  long long V[N];
  std::fill_n(V, max_depth + 1, 0ll);
  fr(i,0,N) {
    long long v;
    std::cin >> v;
    V[D[i]] = V[D[i]] xor v;
  }
  long long mask = 1ll;
  while(mask <= max_depth) mask <<= 1;
  long long cache[mask];
  mask -= 1;
  if(mask < 128) {
    for(long long i = 0; i <= mask; ++i) {
      long long res = 0ll;
      for(long long j = 0; j <= std::min(i, max_depth); ++j) {
        if(((i xor j) & j) == 0) res = res xor V[j];
      }
      cache[i] = res;
    }
  } else {
    long long orig_mask = mask;
    mask >>= 6;
    long long d = mask + 1;
    for(long long i = 0; i <= mask; ++i) {
      long long res[64];
      std::fill_n(res, 64, 0ll);
      for(long long j = 0; j <= std::min(i, max_depth); ++j) {
        if(((i xor j) & j) == 0) {
          fr(k,0,64) {
            if(k * d + j <= max_depth) res[k] = res[k] xor V[k * d + j];
          }
        }
      }
      for(long long k = 0; k < 64; ++k) {
        long long out = 0ll;
        for(long long j = 0; j < 64; ++j) {
          if(((k xor j) & j) == 0) out = out xor res[j];
        }
        cache[k * d + i] = out;
      }
    }
    mask = orig_mask;
  }
  fr(i,0,Q) {
    long long d;
    std::cin >> d;
    d = base + 1ll - d;
    d = d & mask;
    std::cout << cache[d] << std::endl;
  }
  return 0;
}
