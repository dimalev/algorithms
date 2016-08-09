#include <iostream>

int main() {
  unsigned long long n, m, c;
  std::cin >> n >> m >> c;
  unsigned long long z = 1, t = n + m - c - 1;
  for(unsigned long long i = 2; i <= t; z *= i, ++i);
  std::cout << z << std::endl;
}
