// n = A + B, A <= B
// A = a * x; => A mod a = 0, A >= a
// B = b * y; => B mod b = 0, B >= b > a
// a < b => B > A

#include <iostream>
#include <vector>
#include <set>
#include <iterator>
#include <algorithm>

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else

#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)
v#define UNIT_TESTS()

#endif

constexpr int MAX_N = 150000;
constexpr int MAX_P = 30000;
constexpr int prime_limit = std::sqrt(MAX_N);
constexpr int primes_count = 13848;
int primes[primes_count];

std::vector<int> get_divisors(int V, int limit = -1) {
  std::vector<int> divisors;
  if(V == 1) return divisors;
  int V2 = sqrt(V);
  for(int i = 0; i < primes_count && primes[i] <= V2; ++i) {
    if(limit != -1 && primes[i] >= limit) break;
    while(V % primes[i] == 0) {
      divisors.push_back(primes[i]);
      V /= primes[i];
      V2 = sqrt(V);
    }
    if(V == 1) return divisors;
  }
  if(limit == -1 || V < limit) divisors.push_back(V);
  return divisors;
}

int build_combination(std::vector<int> &divisors, int comb) {
  int i = 0, res = 1;
  while(comb > 0) {
    if(comb % 2 == 1) res *= divisors[i];
    comb >>= 1;
    ++i;
  }
  return res;
}

int count(int N) {
  int res = 0;
  int N2 = N / 2;
  std::set<int> As;
  for(int A = 1; A < N; ++A) {
    std::vector<int> divs_a = get_divisors(A);
    int total_combs_a = 1 << divs_a.size();
    for(int comb_a = 0; comb_a < total_combs_a; ++comb_a) {
      As.insert(build_combination(divs_a, comb_a));
    }
  }
  for(int a : As) {
    int max_x = N / a;
    std::set<int> Bs;
    for(int x = 1; x <= max_x; ++x) {
      int B = N - x * a;
      if(B == 0 ) continue;
      std::vector<int> divs_b = get_divisors(B, a);
      int total_combs_b = 1 << divs_b.size();
      for(int comb_b = 0; comb_b < total_combs_b; ++comb_b) {
        int new_b = build_combination(divs_b, comb_b);
        if(new_b >= a) continue;
        Bs.insert(new_b);
      }
    }
    res += Bs.size();
    TRACE(a << ": ");
#ifdef ALGO_DEBUG
    std::copy(Bs.begin(), Bs.end(), std::ostream_iterator<int>(std::cerr, " "));
    std::cerr << std::endl;
#endif
  }
  return res;
}

void test_divisors_builder() {
  int T;
  std::cin >> T;
  while(T--) {
    int V;
    std::cin >> V;
    std::vector<int> divisors = get_divisors(V);
    std::copy(divisors.begin(), divisors.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
  }
}

void test_combination_builder() {
  int T;
  std::cin >> T;
  while(T--) {
    int n;
    std::cin >> n;
    std::vector<int> divs(n);
    for(int i = 0; i < n; ++i) std::cin >> divs[i];
    int comb_count;
    std::cin >> comb_count;
    for(int i = 0; i < comb_count; ++i) {
      int comb;
      std::cin >> comb;
      if(i > 0) std::cout << " ";
      std::cout << build_combination(divs, comb);
    }
    std::cout << std::endl;
  }
}

void unit_tests() {
  test_divisors_builder();
  test_combination_builder();
}

int main() {
  UNIT_TESTS();
  int N;
  std::cin >> N;
  std::cout << count(N) << std::endl;
  return 0;
}
