#include <iostream>
#include <cstring>

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else

#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)
#define UNIT_TESTS()

#endif

constexpr long long MOD = 1e9 + 7;
constexpr long long MAX = 500001;

void unit_tests() {
}

long long inv(long long x, long long P) {
  if(x == 1) return 1;
  long long i = inv(P % x, P);
  return P - ((P / x) * i) % P;
}

long long F[MAX], F_end = 2;

long long fack(long long N) {
  if(N < F_end) return F[N];
  for(;F_end <= N; ++F_end) {
    F[F_end] = (F[F_end - 1] * F_end) % MOD;
  }
  return F[N];
}

long long C(long long N, long long k) {
  long long top = fack(N);
  long long bot = (fack(k) * fack(N - k)) % MOD;
  return (top * inv(bot, MOD)) % MOD;
}

long long count(long long a, long long b) {
  long long m = std::min(a, b), res = 0;
  for(long long i = 1; i <= m; ++i) {
    res = (res + (C(a, i) * C(b, i))) % MOD;
  }
  return res;
}

void solve(int q) {
  char S[MAX];
  std::cin >> S;
  long long C[4], l = std::strlen(S);
  C[0] = C[1] = C[2] = C[3] = 0;
  for(int i = 0; i < l; ++i) {
    ++C[S[i] - 'a'];
  }
  long long only_a = count(C[0], C[1]);
  long long only_b = count(C[2], C[3]);
  long long R = (only_a * only_b + only_a + only_b) % MOD;
  std::cout << R << "\n";
}

int main() {
  UNIT_TESTS();
  F[0] = F[1] = 1;
  int Q;
  std::cin >> Q;
  for(int q = 1; q <= Q; ++q) {
    solve(q);
  }
  return 0;
}
