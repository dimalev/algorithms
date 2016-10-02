#include <iostream>

const int MOD = 1000000007;

long long inv(long long x, long long P) {
  if(x == 1) return 1;
  long long i = inv(P % x, P);
  return P - ((P / x) * i) % P;
}

long long f(long long st, long long k) {
  long long o = 1;
  for(long long i = st; i < k; ++i) o = (o * i) % MOD;
  return o;
}

int C(int n, int k) {
  long long top = f(k + 1, n);
  long long bot = f(2, n - k);
#ifdef ALGO_DEBUG
  std::cerr << n << " " << k << ":" << std::endl;
  std::cerr << top << " / " << bot << std::endl;
#endif
  return (top * inv(bot, MOD)) % MOD;
}

int main() {
  int n, k;
  std::cin >> n >> k;
  int summs[k], count = n - (k * (k - 1)) / 2;
  if(count <= 0) {
    std::cout << 0 << std::endl;
    return 0;
  }
  std::cout << C(count + k, k - 1) << std:: endl;
  return 0;
}
