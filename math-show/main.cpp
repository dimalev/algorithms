#include <iostream>

#define fr(v,s,e) for(long long v = s; v < e; ++v)
#define fl(v,s,e) for(long long v = s; v > e; --v)

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

long long N, K;
long long M, V[45], totals[45];

int main() {
#ifdef UNITS
  unit_tests();
  return 0;
#endif
  std::cin >> N >> K >> M;
  long long total = 0ll;
  fr(i,0,K) {
    std::cin >> V[i];
    total += V[i];
    totals[i] = total;
  }
  long long max_count = 0;
  fr(i,0,N+1) {
    if(i * total > M) break;
    long long count = (K + 1) * i; // completely solved tasks
    long long time = M - i * totals[K - 1]; // time left for solutions
    long long tasks = N - i;
    fr(i,0,K) {
      long long solve = std::min(time / V[i], tasks);
      time -= solve * V[i];
      count += solve;
      tasks = solve;
    }
    if(count > max_count) {
      TRACE_LINE(count << " for " << i << " completely solved tasks");
      max_count = count;
    }
  }
  std::cout << max_count << std::endl;
  return 0;
}
