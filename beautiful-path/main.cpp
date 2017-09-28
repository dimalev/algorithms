#include <iostream>
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
  std::set<std::pair<int, int>> C[1024];
  fr(i,0,M) {
    int u, v, c;
    std::cin >> u >> v >> c;
    C[c].emplace(u, v);
  }
  int A, B;
  std::cin >> A >> B;
  fr(i,1,1024) {
    int roots[N+1];
    fr(j,1,N+1) roots[j] = j;
    fr(j,1,i+1) {
      if((j & i) != j) continue;
      TRACE_LINE("price: " << i << " " << j);
      for(auto &edge : C[j]) {
        int l = edge.first, r = edge.second;
        int lr = roots[l], rr = roots[r];
        while(lr != roots[lr]) {
          int nlr = roots[roots[lr]];
          roots[lr] = nlr;
          lr = nlr;
        }
        while(rr != roots[rr]) {
          int nrr = roots[roots[rr]];
          roots[rr] = nrr;
          rr = nrr;
        }
        if(rr != lr) {
          roots[rr] = lr;
        }
      }
    }
    int l = A, r = B;
    int lr = roots[l], rr = roots[r];
    while(lr != roots[lr]) {
      int nlr = roots[roots[lr]];
      roots[lr] = nlr;
      lr = nlr;
    }
    while(rr != roots[rr]) {
      int nrr = roots[roots[rr]];
      roots[rr] = nrr;
      rr = nrr;
    }
    if(lr == rr) {
      std::cout << i << std::endl;
      return 0;
    }
  }
  std::cout << -1 << std::endl;
  return 0;
}
