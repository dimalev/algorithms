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

void mergeSort(int S, int E, int *A) {
  int M = (S + E) / 2;
  if(E - S > 2) {
    mergeSort(S, M, A);
    mergeSort(M, E, A);
  }
  int *T = new int[E - S];
  int a = S, b = M, i = 0;
  while(a < M && b < E) {
    if(A[a] < A[b]) {
      T[i] = A[a];
      ++a;
    } else {
      T[i] = A[b];
      ++b;
    }
    ++i;
  }
  while(a < M) T[i++] = A[a++];
  while(b < E) T[i++] = A[b++];
  fr(i,0,E-S) A[S + i] = T[i];
  delete[] T;
}

void mergeSort(int N, int *A) {
  mergeSort(0, N, A);
}

int main() {
#ifdef UNITS
  unit_tests();
  return 0;
#endif
  int N;
  std::cin >> N;
  int *A = new int[N];
  fr(i,0,N) {
    std::cin >> A[i];
  }
  mergeSort(N, A);
  fr(i,0,N) {
    if(i > 0) std::cout << " ";
    std::cout << A[i];
  }
  std::cout << std::endl;
  delete[] A;
  return 0;
}
