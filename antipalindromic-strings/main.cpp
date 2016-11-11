#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

constexpr long long MOD = 1e9 + 7LL;

long long pow2(long long number, long long power) {
  if(power == 0) return 1;
  if(power == 1) return number;
  long long nextPower = power / 2;
  long long newModifier = power % 2;
  long long newNumber = pow2(number, nextPower);
  newNumber = (newNumber * newNumber) % MOD;
  if(newModifier == 1) newNumber = (newNumber * number) % MOD;
  return newNumber;
}

void solve() {
  int N, M;
  std::cin >> N >> M;
  if(N == 1) std::cout << M << std::endl;
  else std::cout << ((((pow2(M - 2, N - 2) * (M - 1)) % MOD) * M) % MOD) << std::endl;
}

int main() {
  int T;
  std::cin >> T;
  while(T--) solve();
  return 0;
}
