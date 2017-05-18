#include <iostream>

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else

#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)
#define UNIT_TESTS()

#endif

using ll = long long;

void unit_tests() {
}

int main() {
  UNIT_TESTS();
  ll n, a;
  std::cin >> n >> a;
  ll best = 0, best_one, best_two;
  for(ll d = 0; d < 5000LL; ++d) {
    ll x = a + d;
    ll k = n - x;
    if(k < a) break;
    ll one = (x / 5000 + std::min(1LL, x % 5000)) * 5000 - x;
    ll two = (k / 5000 + std::min(1LL, k % 5000)) * 5000 - k;
    ll good = one % 500 + two % 500;
    best = std::max(best, good);
  }
  std::cout << best << std::endl;
  return 0;
}
