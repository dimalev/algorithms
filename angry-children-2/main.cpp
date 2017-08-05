#include <iostream>
#include <algorithm>

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
  int N, K;
  std::cin >> N >> K;
  long long V[N];
  fr(i,0,N) std::cin >> V[i];
  std::sort(V, V + N);
  // long long S = 0;
  // fr(i,0,K) S += V[i];
  // long long M = S;
  // fr(i,K,N) {
  //   S += V[i] - V[i - K];
  //   if(S < M) M = S;
  // }
  // std::cout << M << std::endl;
  long long C[K + 1];
  long long S[K + 1];
  std::fill_n(C, K + 1, 0);
  std::fill_n(S, K + 1, 0);
  fl(i,N - 1,-1) {
    int min = std::min(N - (i + 1), K);
    fl(j, min, 0) {
      if(j == N - (i + 1) || -(j - 1) * V[i] + S[j - 1] + C[j - 1] <= C[j]) {
        S[j] = S[j - 1] + V[i];
        C[j] = -(j - 1) * V[i] + S[j - 1] + C[j - 1];
      } 
    }
    TRACE(V[i] << "\t:");
    fr(j, 0, K + 1) {
      TRACE(S[j] << "\t");
    }
    TRACE("\t");
    fr(j, 0, K + 1) {
      TRACE(C[j] << "\t");
    }
    TRACE_LINE("");

  }
  std::cout << C[K];
  return 0;
}
