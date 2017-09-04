#include <iostream>
#include <vector>
#include <algorithm>

#define fr(v,s,e) for(int v = s; v < e; ++v)
#define fl(v,s,e) for(int v = s; v > e; --v)

#ifdef UNITS
#include "../test/units.cpp"
#endif

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else
#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)
#endif

#ifdef UNITS
void unit_tests() {
  test_header("test units");
}
#endif

int main() {
#ifdef UNITS
  unit_tests();
  return 0;
#endif
  std::vector<long long> primes;
  primes.push_back(2);
  for(int i = 3; i <= 1000000; i += 2) {
    bool is_prime = true;
    for(const auto& j : primes) {
      if(j * j > i) break;
      if(i % j == 0) {
        is_prime = false;
        break;
      }
    }
    if(is_prime) primes.push_back(i);
  }
  int total_primes = primes.size();
  // std::cout << *primes.rbegin() << " / " << total_primes << std::endl;
  // return 0;
  long long N, x, y;
  std::cin >> N >> x >> y;
  if(x >= y) {
    int even[total_primes];
    std::fill_n(even, total_primes, 0ll);
    long long nums[N];
    fr(i,0,N) {
      long long v;
      std::cin >> v;
      nums[i] = v;
      fr(j,0,total_primes) {
        if(primes[j] * primes[j] > v) break;
        if(v % primes[j] == 0) {
          ++even[j];
          while(v % primes[j] == 0) {
            v /= primes[j];
          }
        }
      }
      if(nums[i] > 1) {
        auto prime_it = std::lower_bound(primes.begin(), primes.end(), nums[i]);
        even[std::distance(primes.begin(), prime_it)]++;
      }
    }
    std::vector<std::pair<int, int>> sorted_primes;
    fr(i,0,total_primes) {
      sorted_primes.emplace_back(even[i], i);
    }
    std::sort(sorted_primes.rbegin(), sorted_primes.rend());
    long long min = 0;
    fr(i,0,N) {
      long long mod = nums[i] % primes[sorted_primes[0].second];
      if(mod > 0) {
        min += std::min(x, y * (primes[sorted_primes[0].second] - mod));
      }
    }
    fr(i,1,total_primes) {
      // TRACE_LINE(primes[sorted_primes[i].second] << " -> " << even[sorted_primes[i].second]);
      if((N - sorted_primes[i].first) * y > min) continue;
      long long cost = 0;
      fr(j,0,N) {
        long long mod = nums[j] % primes[sorted_primes[i].second];
        if(mod > 0) {
          cost += std::min(x, y * (primes[sorted_primes[i].second] - mod));
          if(cost > min) break;
        }
      }
      if(cost < min) min = cost;
    }
    std::cout << min << std::endl;
  } else {
    long long even[total_primes];
    std::fill_n(even, total_primes, 0ll);
    fr(i,0,N) {
      long long v;
      std::cin >> v;
      fr(j,0,total_primes) {
        if(primes[j] * primes[j] > v) break;
        if(v % primes[j] == 0) {
          ++even[j];
          while(v % primes[j] == 0) {
            v /= primes[j];
          }
        }
      }
      if(v > 1) {
        auto prime_it = std::lower_bound(primes.begin(), primes.end(), v);
        even[std::distance(primes.begin(), prime_it)]++;
      }
    }
    int max = 0;
    fr(i,1,total_primes) {
      if(even[max] > even[i]) max = i;
    }
    std::cout << ((N - even[max]) * y) << std::endl;
  }
  return 0;
}
