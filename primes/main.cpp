#include <iostream>
#include <cmath>

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else

#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)
#define UNIT_TESTS()

#endif

constexpr int MAX_N = sqrt(1000000000);
constexpr int MAX_P = 100000;
int primes_count = 1;
int primes[MAX_P];
int primes_sqr[MAX_P];
constexpr int prime_limit = std::sqrt(MAX_N);

void unit_tests() {
}

int main() {
  UNIT_TESTS()
  primes[0] = 2;
  int twins = 0;
   std::cout << "{ 2";
  for(int i = 3; i < MAX_N; i += 2) {
    bool is_prime = true;
    for(int j = 0; j < primes_count; ++j) {
      if(i % primes[j] == 0) {
        is_prime = false;
        break;
      }
      if(i < primes_sqr[j]) break;
    }
    if(is_prime) {
      if(primes_count >= MAX_P) {
        std::cerr << "(EE) on " << i << " maximum overbound!\n";
        return -1;
      }
      primes[primes_count] = i;
      if(i >= prime_limit) primes_sqr[primes_count] = MAX_N;
      else primes_sqr[primes_count] = i * i;
      // if(primes[primes_count] - primes[primes_count - 1] == 2) std::cerr << ++twins << std::endl;
      ++primes_count;
           std::cout << ", " << i;
    }
  }
  // std::cout << twins << std::endl;
   std::cout << "}" << std::endl;
   std::cerr << "count: " << primes_count << std::endl;
  return 0;
}
