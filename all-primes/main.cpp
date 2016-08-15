#include <iostream>
#include <vector>

int main() {
  int n;
  std::cin >> n;
  std::vector<int> primes;
  if(n >= 2) primes.push_back(2);
  for(int i = 3; i <= n; i += 2) {
    bool isPrime = true;
    for(int prime : primes) {
      if(i % prime == 0) {
        isPrime = false;
        break;
      }
    }
    if(isPrime) primes.push_back(i);
  }
  std::cout << primes.size() << std::endl;
  return 0;
}
