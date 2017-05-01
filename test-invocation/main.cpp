#include <iostream>
#include <set>

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else

#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)
#define UNIT_TESTS()

#endif

void unit_tests() {
}

long L[50];
int depends[50][50];

long count_total(int root, long weight) {
  long children = 0;
  for(int i = 1; i <= depends[root][0]; ++i) {
    children += count_total(depends[root][i], weight * 2);
  }
  return children + L[root] * weight;
}

int main() {
  UNIT_TESTS();
  int N;
  std::cin >> N;
  long total_one = 0;
  for(int n = 0; n < N; ++n) {
    std::cin >> L[n];
    total_one += L[n];
  }
  std::set<int> root;
  for(int n = 0; n < N; ++n) {
    root.insert(n);
  }
  for(int n = 0; n < N; ++n) {
    std::cin >> depends[n][0];
    for(int i = 1; i <= depends[n][0]; ++i) {
      int k;
      std::cin >> k;
      --k;
      depends[n][i] = k;
      root.erase(k);
    }
  }
  long total_two = count_total(*root.begin(), 1);
  std::cout << total_one << " " << total_two << "\n";
  return 0;
}
