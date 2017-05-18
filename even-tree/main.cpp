#include <iostream>
#include <set>
#include <algorithm>
#include <string>

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
  std::string line;
  std::cin >> line;
  std::cout << line << std::endl;
}
#endif

int main() {
#ifdef UNITS
  unit_tests();
  return 0;
#endif
  int N, M;
  std::cin >> M >> N;
  std::set<int> E[100];
  for(int i = 0; i < N; ++i) {
    int a, b;
    std::cin >> a >> b;
    --a; --b;
    E[a].insert(b);
    E[b].insert(a);
  }
  int subtree[100], res = 0;
  std::fill_n(subtree, 100, 1);
  for(int i = 0; i < M; ++i) {
    TRACE_LINE((i + 1) << " " << E[i].size());
    if(E[i].size() <= 1) {
      int a = i;
      while(E[a].size() == 1) {
        int b = *E[a].begin();
        E[a].erase(b);
        if(subtree[a] % 2 == 0) {
          ++res;
        } else {
          subtree[b] += subtree[a];
        }
        TRACE_LINE(":: " << (a + 1) << " " << (b + 1) << " size=" << subtree[a]);
        E[b].erase(a);
        a = b;
      }
    }
  }
  std::cout << res << std::endl;
  return 0;
}
