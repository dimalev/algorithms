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
  int N;
  std::cin >> N;
  std::vector<std::pair<int, int>> top, bottom;
  top.resize(N); bottom.resize(N);
  fr(i,0,N) {
    std::cin >> top[i].first;
  }
  fr(i,0,N) {
    std::cin >> bottom[i].first;
    bottom[i].second = i;
  }
  std::sort(bottom.begin(), bottom.end());
  std::sort(top.rbegin(), top.rend());
  fr(i,0,N) {
    top[i].second = top[i].first;
    top[i].first = bottom[i].second;
  }
  std::sort(top.begin(), top.end());
  fr(i,0,N) {
    if(i > 0) std::cout << " ";
    std::cout << // top[i].first << "/" << 
      top[i].second;
  }
  std::cout << std::endl;
  return 0;
}
