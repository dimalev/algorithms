#include <iostream>
#include <array>
#include <cstring>

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else

#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)
#define UNIT_TESTS()

#endif

constexpr long long N_MAX = 100001;
constexpr long long MOD = 1e9 + 7;

long long F[N_MAX]; // facotrials
long long IF[N_MAX]; // inverse factorials


long long inv(long long x) {
  if(x == 1) return 1;
  long long i = inv(MOD % x);
  return MOD - ((MOD / x) * i) % MOD;
}

long long C(long long N, long long k) {
  return (F[N] * IF[k] % MOD) * IF[N - k] % MOD;
}

long long count(array<long long, 26> &histo, long long L) {
  long long line[L];
  memset(line, 0, L * sizeof(long long));
  line[0] = 1;
  for(int i = 0; i < 26; ++i) {
    // for each char;
    for(long l = L; l > 0; --l) {
      for(int i = 1; i <= histo[i]; ++i) {
        if(L % 2 != 1 || i % 2 != 1) {
          line[l] = (line[l] + line[L - i] * C(histo[i], i)) % MOD;
        }
      }
    }
  }
  long long res = 0;
  for(int i = 1; i <= L; ++i) res = (res + line[i]) % MOD;
  return res;
}


void unit_tests() {
}

int main() {
  UNIT_TESTS();
  F[0] = 1; F[1] = 1;
  IF[0] = 1; IF[1] = 1;
  for(long long i = 2; i < N_MAX; ++i) {
    F[i] = i * F[i - 1] % MOD;
    IF[i] = inv(F[i]);
  }
  char L[N_MAX];
  int N, Q;
  cin >> N >> Q;
  cin >> L;
  for(int i = 0; i < N; ++i) L[i] -= 'a';
  while(Q--) {
    int t;
    cin >> t;
    if(t == 1) {
      int s, f, d;
      cin >> s >> f >> d;
      for(int i = s; i <= f; ++i) L[i] = (L[i] + d) % 26;
    } else {
      int s, f;
      cin >> s >> f;
      array<long long, 26> histo;
      for(int i = s; i <= f; ++i) histo[L[i]]++;
      cout << count(histo, f - s + 1) << "\n";
    }
  }
  return 0;
}
