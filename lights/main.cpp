#include <iostream>

typedef unsigned long long ull;
const ull MOD = 1000000007LL;

ull pow2(ull power) {
  ull res = 1LL;
  while(power > 0) {
    if(power < 25) {
      res = res * (1LL << power) % MOD;
      power = 0;
    } else {
      res = res * (1LL << 25) % MOD;
      power -= 25;
    }
  }
  return res;
}

int main() {
  ull n, k;
  std::cin >> n >> k;
  if(k > 1) {
    std::cout << (pow2(k - 1LL) * (n - k + 2LL)) % MOD;
  } else std::cout << (n + 1);
}
