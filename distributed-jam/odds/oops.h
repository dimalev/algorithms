constexpr long long N = 100;
constexpr long long MOD = 1e9 + 7;

long long GetN() { return N; }

long long GetNumber(long long id) {
  return (id * 149993) % MOD;
}
