#include <iostream>
#include <array>
#include <algorithm>
#include <cmath>
#include <iterator>

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else

#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)

#endif

const int MAX_N = 1000000000;
constexpr int MAX_PRIME = 31622;

int primes[MAX_PRIME];
int total_primes;

void fill_primes(int max) {
  total_primes = 1;
  primes[0] = 2;
  for(int i = 3; i <= max; i += 2) {
    bool is_prime = true;
    for(int j = 1; j < total_primes; ++j) {
      if(i % primes[j] == 0) {
        is_prime = false;
        break;
      }
    }
    if(is_prime) primes[total_primes++] = i;
  }
}

int find_divisors(int p, std::array<int, 32> &divisors) {
  int num = 0;
  for(int i = 0; i < total_primes && p >= primes[i]; ++i) {
    if(p % primes[i] == 0) divisors[num++] = primes[i];
  }
  return num;
}

long long coprimes(int p, int N, const std::array<int, 32> &divisors, int count) {
  long long result = N - 1; // we imagine all are coprime to p, except '1'
  TRACE_LINE(p << " has " << count << " divisors");
  int perms = 1 << count;
  for(int i = 1; i < perms; i++) {
    int ones = 0;
    int value = 1;
    int i2 = i, j = 0;
    while(i2 > 0) {
      if(i2 % 2 == 1) {
        value *= divisors[j];
        ones++;
      }
      ++j;
      i2 /= 2;
    }
    TRACE_LINE(p << " / " << value);
    if(ones % 2 == 1) result -= N / value;
    else result += N / value;
  }
  return result;
}

int main() {
  int N;
  std::cin >> N;
  int N2 = std::sqrt(N);
  fill_primes(N2);
#ifdef ALGO_DEBUG
  std::copy(primes, primes + total_primes, std::ostream_iterator<int>(std::cerr, " "));
  std::cerr << std::endl;
#endif
  long long count = 0;
  for(int p = 2; p <= N2; p++) {
    std::array<int, 32> divisors;
    int divisors_count = find_divisors(p, divisors);
    long long copsN = coprimes(p, N / p, divisors, divisors_count);
    long long copsP = coprimes(p, p, divisors, divisors_count);
    TRACE_LINE(p << ": " << copsN << " - " << copsP);
    count += copsN - copsP;
  }
  std::cout << count << std::endl;
  return 0;
}
