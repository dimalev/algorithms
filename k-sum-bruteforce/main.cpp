#include <iostream>
#include <vector>
#include <iterator>
#include <stack>

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

bool search(const std::vector<int> &elements, int count, int sum, int limit) {
  if(count == 0) return sum == 0;
  if(sum < 0) return false;
  for(int i = count - 1; i < limit; ++i) {
    if(search(elements, count - 1, sum - elements[i], i)) {
      std::cout << elements[i] << "\n";
      return true;
    }
  }
  return false;
}

int main() {
  UNIT_TESTS();
  int k, sum, e;
  std::cin >> k >> sum;
  std::vector<int> E;
  while(std::cin >> e) E.push_back(e);
  search(E, k, sum, E.size());
  return 0;
}
