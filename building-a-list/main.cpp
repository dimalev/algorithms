#include <iostream>
#include <algorithm>

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

int n;
char buffer[51], prefix[51];


void print_combinations(int i, int j) {
  if(i >= n) return;
  prefix[j] = buffer[i];
  prefix[j + 1] = '\0';
  std::cout << prefix << "\n";
  print_combinations(i + 1, j + 1);
  prefix[j] = '\0';
  print_combinations(i + 1, j);
}

int main() {
  UNIT_TESTS();
  int T;
  std::cin >> T;
  while(T--) {
    std::cin >> n;
    std::cin >> buffer;
    std::sort(buffer, buffer + n);
    print_combinations(0, 0);
  }
  return 0;
}
