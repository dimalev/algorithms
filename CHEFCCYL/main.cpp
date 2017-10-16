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
  return LB[e] - (s > 0 ? LB[s-1] : 0);
}

int left(const std::vector<int> &LB, int s, int e) {
  if(s == e) return 0;
  assert(s < e);
  return distance(LB, s, e-1);
}

int right(const std::vector<int> &LB, int s, int e) {
  if(s == e) return 0;
  assert(s < e);
  return distance(LB, e, LB.size()-1) +
    (s > 0 ? distance(LB, 0, s-1) : 0);
}

int closer(const std::vector<int> &LB, int s, int e) {
  if(s == e) return 0;
  if(s > e) std::swap(s, e);
  return std::min(right(LB, s, e), left(LB, s, e));
}

void build(const std::vector<int> &L, std::vector<int> &B) {
  int N = L.size(), S = 0;
  B.resize(N);
  fr(i,0,N) {
    S += L[i];
    B[i] = S;
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
    std::vector<int> L[N], LB[N], D(N), DB(N), T(N), TB(N);
    int A[N];
    fr(i,0,N) {
      std::cin >> A[i];
      L[i].resize(A[i]);
      fr(j,0,A[i]) {
        std::cin >> L[i][j];
      }
      build(L[i], LB[i]);
    }
    std::vector<std::pair<int, int>> C(N);
    fr(i,0,N) {
      std::cin >> C[i].first >> C[i].second >> D[i];
      --C[i].first; --C[i].second;
    }
    build(D, DB);
    fr(i,0,N) {
      int i1 = (i + N - 1) % N;
      int v1 = C[i].first, v2 = C[i1].second;
      if(v1 > v2) std::swap(v1, v2);
      T[i] = closer(LB[i], v1, v2);
    }
    build(T, TB);
    fr(i,0,Q) {
      int v1, v2, c1, c2;
      std::cin >> v1 >> c1 >> v2 >> c2;
      --c1; --c2; --v1; --v2;
      if(c1 > c2) {
        std::swap(v1, v2);
        std::swap(c1, c2);
      }
      int c1m = (c1 + N - 1) % N;
      int c2m = (c2 + N - 1) % N;
      int c1p = (c1 + 1) % N;
      int c2p = (c2 + 1) % N;
      TRACE_LINE("== " << (c1+1) << "(" << (v1+1) << ") -> " << (c2+1) << "(" << (v2+1) << ")");
      int leave_c1 = closer(LB[c1], C[c1].first, v1);
      int inter = left(DB, c1, c2);
      int transit = c1 != c2m ? distance(TB, c1p, c2m) : 0;
      int enter_c2 = closer(LB[c2], C[c2m].second, v2);
      TRACE_LINE((c1+1) << ": " << (C[c1].first+1) << " -> " << (v1+1) << ": " << leave_c1);
      TRACE_LINE((c1+1) << " -> " << (c2+1) << ": " << inter);
      TRACE_LINE((c1p+1) << " -> " << (c2m+1) << ": " << transit);
      TRACE_LINE((c2+1) << ": " << (C[c2m].second+1) << " -> " << (v2+1) << ": " << enter_c2);
      int one = leave_c1 + inter + enter_c2 + transit;
      TRACE_LINE("== " << (c2+1) << "(" << (v2+1) << ") -> " << (c1+1) << "(" << (v1+1) << ")");
      leave_c1 = closer(LB[c1], C[c1m].second, v1);
      inter = right(DB, c1, c2);
      if(c1m == c2) {
        transit = 0;
      } else {
        if(c1m < c2p) {
          transit = distance(TB, 0, c1m) + distance(TB, c2p, N-1);
        } else {
          transit = distance(TB, c2p, c1m);
        }
      }
      enter_c2 = closer(LB[c2], C[c2].first, v2);
      TRACE_LINE((c1+1) << ": " << (C[c1m].second+1) << " -> " << (v1+1) << ": " << leave_c1);
      TRACE_LINE((c1+1) << " -> " << (c2+1) << ": " << inter);
      TRACE_LINE((c1m+1) << " -> " << (c2p+1) << ": " << transit);
      TRACE_LINE((c2+1) << ": " << (C[c2].first+1) << " -> " << (v2+1) << ": " << enter_c2);
      int two = leave_c1 + inter + enter_c2 + transit;
      std::cout << std::min(one, two) << std::endl;
    }
  }
  return 0;
}
