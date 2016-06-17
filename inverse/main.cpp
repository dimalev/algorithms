#include <iostream>
#include <limits>
#include <set>

std::set<long> testing;

long depth;
long maxDepth = 0L;
long maxDepthAll = 0L;
long long avgDepth = 0LL;
long long avgDepthAll = 0LL;

long inv(long x, long P) {
  ++depth;
  if(x == 1) return 1;
  if(testing.find(x) != testing.end()) {
    std::cerr << "Error while counting " << x << std::endl;
    return 0;
  }
  testing.insert(x);
  long i = inv(P % x, P);
  testing.erase(x);
  return P - ((P / x) * i) % P;
}

inline long max(long a, long b) { return a > b ? a : b; }

int main() {
  long P = 1000000007L;
  for(long x = 2L; x < P - 1L; ++x) {
    if(x % 100000L == 0) {
      std::cout << "counting " << (x / 100000L) << ":"
                << " max=" << maxDepth
                << " avg=" << (avgDepth / 100000LL)
                << std::endl;
      maxDepthAll = max(maxDepthAll, maxDepth);
      maxDepth = 0L;
      avgDepthAll += avgDepth;
      avgDepth = 0LL;
    }
    depth = 0L;
    long invX = inv(x, P);
    maxDepth = max(maxDepth, depth);
    avgDepth += depth;

    if(1 != (x * invX) % P) {
      std::cerr << "Failed counting for " << x;
    }
  }
  maxDepthAll = max(maxDepthAll, maxDepth);
  avgDepthAll += avgDepth;
  std::cout << "MAX: " << maxDepthAll << std::endl;
  std::cout << "AVG: " << (avgDepthAll / 1000000006LL) << std::endl;
  return 0;
}
