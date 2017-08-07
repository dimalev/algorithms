#include <iostream>
#include <limits>
#include <set>
#include <queue>

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
  std::multiset<int> sockets;
  int n, m, k;
  std::cin >> n >> m >> k;
  fr(i,0,m) {
    int a, b;
    std::cin >> a >> b;
    int v = 0;
    if(b == 0) {
      v = a;
    } else if(a == n) {
      v = n + b;
    } else if(b == n) {
      v = 3 * n -a;
    } else {
      v = 4 * n - b;
    }
    sockets.insert(v);
    sockets.insert(v + 4 * n);
  }
  std::queue<int> used;
  int best = std::numeric_limits<int>::max();
  for(int v : sockets) {
    TRACE_LINE("pushing " << v);
    used.push(v);
    if(used.size() == k) {
      int f = used.front();
      TRACE_LINE("popping " << f);
      used.pop();
      best = std::min(v - f, best);
    }
  }
  std::cout << best << std::endl;
  return 0;
}
