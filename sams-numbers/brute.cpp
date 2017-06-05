#include <iostream>

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

using ll = long long;

constexpr ll MOD = 1e9+9;

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
  ll s, m, d;
  std::cin >> s >> m >> d;
  ll S[m + 1][s + 1];
  for(ll i = 1; i <= m; ++i) {
    S[i][i] = 1;
    for(ll j = 0; j < i; ++j)
      S[i][j] = 0;
  }
  for(ll i = 2; i <= s; ++i) {
    for(ll j = 1; j <= m; ++j) {
      if(j >= i) continue;
      S[j][i] = 0;
      for(ll k = std::max(1ll, j - d); k <= std::min(m, j + d); ++k) {
        S[j][i] = (S[j][i] + S[k][i - j]) % MOD;
      }
    }
  }
  ll total = 0ll;
  for(ll i = 1; i <= m; ++i) {
    total = (total + S[i][s]) % MOD;
  }
  std::cout << total << std::endl;
  return 0;
}
