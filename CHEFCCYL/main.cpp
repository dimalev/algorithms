#include <iostream>
#include <cassert>
#include <vector>

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

int distance(const std::vector<int> &LB, int s, int e) {
  assert(s > 0);
  if(s == e) return 0;
  assert(s < e);
  int Le = 0;
  --e;
  while(e > 0) {
    Le += LB[e];
    e -= e & -e;
  }
  int Ls = 0;
  --s;
  while(s > 0) {
    Ls += LB[s];
    s -= s & -s;
  }
  return Le - Ls;
}

int left(const std::vector<int> &LB, int s, int e) {
  assert(s > 0);
  if(s == e) return 0;
  assert(s < e);
  return distance(LB, s, e);
}

int right(const std::vector<int> &LB, int s, int e) {
  assert(s > 0);
  if(s == e) return 0;
  assert(s < e);
  return distance(LB, e, LB.size()) +
    (s > 1 ? distance(LB, 1, s) : 0);
}

int closer(const std::vector<int> &LB, int s, int e) {
  assert(s > 0);
  if(s == e) return 0;
  if(s > e) std::swap(s, e);
  return std::min(right(LB, s, e), left(LB, s, e));
}

void build(const std::vector<int> &L, std::vector<int> &B) {
  int N = L.size();
  fr(j,1,N) {
    int k = j;
    while(k < N) {
      B[k] += L[j];
      k += k & -k;
    }
  }
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
  int T;
  std::cin >> T;
  while(T--) {
    int N, Q;
    std::cin >> N >> Q;
    std::vector<int> L[N+1], LB[N+1], D(N+1), DB(N+1), T(N+1), TB(N+1);
    int A[N];
    fr(i,1,N+1) {
      std::cin >> A[i];
      L[i].resize(A[i] + 1);
      LB[i].resize(A[i] + 1);
      fr(j,1,A[i]+1) {
        std::cin >> L[i][j];
      }
      build(L[i], LB[i]);
    }
    std::vector<std::pair<int, int>> C(N+1);
    fr(i,1,N+1) {
      std::cin >> C[i].first >> C[i].second >> D[i];
    }
    build(D, DB);
    fr(i,1,N+1) {
      int i1 = i - 1;
      if(i1 == 0) i1 = N;
      int v1 = C[i].first, v2 = C[i1].second;
      if(v1 > v2) std::swap(v1, v2);
      T[i] = closer(LB[i], v1, v2);
    }
    build(T, TB);
    fr(i,0,Q) {
      int v1, v2, c1, c2;
      std::cin >> v1 >> c1 >> v2 >> c2;
      if(c1 > c2) {
        std::swap(v1, v2);
        std::swap(c1, c2);
      }
      int c1m = c1 - 1;
      if(c1m == 0) c1m = N;
      int c2m = c2 - 1;
      if(c2m == 0) c2m = N;
      int c1p = c1 + 1;
      if(c1p == N + 1) c1p = 1;
      int c2p = c2 + 1;
      if(c2p == N + 1) c2p = 1;
      TRACE_LINE("== " << c1 << "(" << v1 << ") -> " << c2 << "(" << v2 << ")");
      int leave_c1 = closer(LB[c1], C[c1].first, v1);
      int inter = left(DB, c1, c2);
      int transit = c1p <= c2m ? left(TB, c1p, c2m) : 0;
      int enter_c2 = closer(LB[c2], C[c2m].second, v2);
      TRACE_LINE(c1 << ": " << C[c1].first << " -> " << v1 << ": " << leave_c1);
      TRACE_LINE(c1 << " -> " << c2 << ": " << inter);
      TRACE_LINE(c1p << " -> " << c2m << ": " << transit);
      TRACE_LINE(c2 << ": " << C[c2m].second << " -> " << v2 << ": " << enter_c2);
      int one = leave_c1 + inter + enter_c2 + transit;
      TRACE_LINE("== " << c2 << "(" << v2 << ") -> " << c1 << "(" << v1 << ")");
      leave_c1 = closer(LB[c1], C[c1m].second, v1);
      inter = right(DB, c1, c2);
      transit = c1m <= c2p ? right(TB, c1m, c2p) : 0;
      enter_c2 = closer(LB[c2], C[c2].first, v2);
      TRACE_LINE(c1 << ": " << C[c1m].second << " -> " << v1 << ": " << leave_c1);
      TRACE_LINE(c1 << " -> " << c2 << ": " << inter);
      TRACE_LINE(c1m << " -> " << c2p << ": " << transit);
      TRACE_LINE(c2 << ": " << C[c2].first << " -> " << v2 << ": " << enter_c2);
      int two = leave_c1 + inter + enter_c2;
      std::cout << std::min(one, two) << std::endl;
    }
  }
  return 0;
}
