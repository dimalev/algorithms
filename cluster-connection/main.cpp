#include <iostream>

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else

#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)
#define UNIT_TESTS()

#endif

long long MOD = 1e9 + 7;

long long inv(long long x, long long P) {
  if(x == 1) return 1;
  long i = inv(P % x, P);
  return P - ((P / x) * i) % P;
}

long long F(long long v) {
  if(v < 2) return 1;
  long long res = 1;
  for(long long z = 2; z <= v; ++z)
    res = (res * z) % MOD;
  return res;
}

void unit_tests() {
}

int main() {
  UNIT_TESTS();
  int N;
  std::cin >> N;
  std::cout << (F(N - 1) * (((N - 3) * N) * inv(4, MOD) + ((N - 4) * N) * inv(4, MOD))) % MOD;
  return 0;
}
