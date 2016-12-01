#include <vector>
#include <iostream>

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

int main() {
  UNIT_TESTS();
  int n, m, h_min, h_max;
  std::vector<std::vector<int>*> breakpoints;
  std::vector<int> *current_breakpoint = new std::vector<int>;
  breakpoints.push_back(current_breakpoint);
  std::cin >> n;
  int A[n];
  for(int i = 0; i < n; ++i) std::cin >> A[i];
  std::cin >> m >> h_min >> h_max;
  current_breakpoint->push_back(A[0] - h_max);
  for(int i = 1; i < n; ++i) {
    if(A[i] - A[i - 1] < h_min) {
      current_breakpoint = new std::vector<int>;
      breakpoints.push_back(current_breakpoint);
      current_breakpoint->push_back(A[i]);
    } else if(A[i] - A[i - 1] > h_max) {
      current_breakpoint->push_back(A[i]);
      current_breakpoint = new std::vector<int>;
      breakpoints.push_back(current_breakpoint);
      current_breakpoint->push_back(A[i - 1]);
      current_breakpoint->push_back(A[i - 1] + h_max);
    }
  }
  current_breakpoint->push_back(A[n - 1] + h_max);
  return 0;
}
