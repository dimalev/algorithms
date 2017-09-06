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
  int n, k;
  std::cin >> n >> k;
  long long res = 0ll;
  std::vector<std::pair<long long, int>> costs;
  costs.reserve(k);
  fr(i,0,k) {
    long long v;
    std::cin >> v;
    costs.emplace_back(v, i);
  }
  std::make_heap(costs.begin(), costs.end());
  int time[300000];
  fr(i,k,n) {
    long long v;
    std::cin >> v;
    costs.emplace_back(v, i);
    std::push_heap(costs.begin(), costs.end());
    auto pair = costs.front();
    std::pop_heap(costs.begin(), costs.end());
    costs.pop_back();
    res += pair.first * (i - pair.second);
    time[pair.second] = i + 1;
  }
  fr(i,n,n+k) {
    auto pair = costs.front();
    std::pop_heap(costs.begin(), costs.end());
    costs.pop_back();
    res += pair.first * (i - pair.second);
    time[pair.second] = i + 1;
  }
  std::cout << res << std::endl;
  fr(i,0,n) {
    if(i > 0) std::cout << " ";
    std::cout << time[i];
  }
  std::cout << std::endl;
  return 0;
}
