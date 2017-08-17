#include <iostream>

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

int split(const int &S, const int &E, const int &M, int *A) {
  int pivotal = A[M];
  std::swap(A[M], A[E - 1]);
  int pivotalIndex = S;
  fr(i,S,E) {
    if(A[i] < pivotal) {
      std::swap(A[i], A[pivotalIndex]);
      ++pivotalIndex;
    }
  }
  std::swap(A[pivotalIndex], A[E - 1]);
  return pivotalIndex;
}

int main() {
#ifdef UNITS
  unit_tests();
  return 0;
#endif
  int N, M;
  std::cin >> N >> M;
  int *A = new int[N];
  fr(i,0,N) {
    std::cin >> A[i];
  }
  fr(i,0,M) {
    int K;
    std::cin >> K;
    int S = 0, E = N;
    for(;;) {
      int P = split(S, E, K, A);
      TRACE_LINE(S << " -> " << E << ": " << P << " (" << K << ")");
      if(P == K) {
        std::cout << A[K] << std::endl;
        break;
      } else if(P < K) {
        S = P + 1;
      } else {
        E = P;
      }
    }
  }
  return 0;
}
