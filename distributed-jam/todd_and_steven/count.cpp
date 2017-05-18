#include <iostream>

long long mod = 1e9 + 7;

int main() {
  long long sum = 0ll;
  for(long long i = 0; i < 16; ++i) {
    sum = (sum + ((203 + i * 2) ^ (16 + i))) % mod;
    sum = (sum + ((120 + i * 2) ^ i)) % mod;
  }
  std::cout << sum << std::endl;
}
