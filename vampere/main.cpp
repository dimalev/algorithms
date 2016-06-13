#include <iostream>

typedef long long ll;

int main() {
  ll n, M,
    accB = 0LL, // accumulation per straight wins
    fights = 0LL; // fights required so far
  std::cin >> n >> M;
  for(ll i = 0LL; i < n; ++i) {
    ll a, b, c;
    std::cin >> a >> b >> c;
    if(M > a) {
      accB += b;
      M += b;
      fights++;
    } else {
      if(accB <= c) {
        std::cout << -1;
        return 0;
      }
      ll reps = (a - M + accB - c) / (accB - c);
      M += reps * (accB - c) + b;
      fights += (i + 1LL) * reps + 1LL;
      accB += b;
    }
  }
  std::cout << fights;
}
