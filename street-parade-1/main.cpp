#include <vector>
#include <iostream>
#include <iterator>

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else

#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)
#define UNIT_TESTS()

#endif

std::vector<std::vector<int>*> build_breakpoints(int *A, int n, int h_min, int h_max, int m) {
  std::vector<std::vector<int>*> breakpoints;
  std::vector<int> *current_breakpoint = new std::vector<int>;
  breakpoints.push_back(current_breakpoint);
  current_breakpoint->push_back(A[0] - h_max);
  current_breakpoint->push_back(A[0]);
  int current_breakpoint_length = h_max;
  for(int i = 1; i < n; ++i) {
    if(A[i] - A[i - 1] < h_min) {
      if(current_breakpoint_length < m) {
        current_breakpoint->clear();
      } else {
        current_breakpoint = new std::vector<int>;
        breakpoints.push_back(current_breakpoint);
      }
      current_breakpoint_length = 0;
      current_breakpoint->push_back(A[i]);
    } else if(A[i] - A[i - 1] > h_max) {
      current_breakpoint_length += h_max;
      current_breakpoint->push_back(A[i - 1] + h_max);
      if(current_breakpoint_length < m) {
        current_breakpoint->clear();
      } else {
        current_breakpoint = new std::vector<int>;
        breakpoints.push_back(current_breakpoint);
      }
      current_breakpoint_length = h_max;
      current_breakpoint->push_back(A[i] - h_max);
      current_breakpoint->push_back(A[i]);
    } else {
      current_breakpoint_length += A[i] - A[i - 1];
      current_breakpoint->push_back(A[i]);
    }
  }
  current_breakpoint_length += h_max;
  if(current_breakpoint_length < m) {
    delete current_breakpoint;
    breakpoints.pop_back();
  } else {
    current_breakpoint->push_back(A[n - 1] + h_max);
  }
  return breakpoints;
}

void test_breakpoints() {
  int T;
  std::cin >> T;
  while(T--) {
    int m, h_min, h_max, n;
    std::cin >> m >> h_min >> h_max >> n;
    int A[n];
    for(int i = 0; i < n; ++i) std::cin >> A[i];
    std::vector<std::vector<int>*> bp = build_breakpoints(A, n, h_min, h_max, m);
    for(const std::vector<int>* line : bp) {
      std::copy(line->begin(), line->end(), std::ostream_iterator<int>(std::cout, " "));
      std::cout << std::endl;
      delete line;
    }
  }
}

void unit_tests() {
  test_breakpoints();
}

int main() {
  UNIT_TESTS();
  int n, m, h_min, h_max;
  std::cin >> n;
  int A[n];
  for(int i = 0; i < n; ++i) std::cin >> A[i];
  std::cin >> m >> h_min >> h_max;
  std::vector<std::vector<int>*> breakpoints = build_breakpoints(A, n, h_min, h_max, m);
  int min_inner = m - 2 * h_max,
    max_inner = m - 2 * h_min;
  for(std::vector<int>* points : breakpoints) {
    int s = 0, f = 1;
    while(f < points->size()) {
      if((*points)[f] - (*points)[s] >= m) {
        if(f - s == 1) {
          std::cout << (*points)[s] << std::endl;
          return 0;
        }
        if(f - s == 2) {
          std::cout << std::max((*points)[s], (*points)[s + 1] + h_min - m) << std::endl;
          return 0;
        }
        int inner = (*points)[f - 1] - (*points)[s + 1];
        if((inner >= min_inner) && (inner <= max_inner)) {
          std::cout << std::max((*points)[s], (*points)[f - 1] + h_min - m) << std::endl;
          return 0;
        }
        if(inner < min_inner) ++f;
        if(inner > max_inner) ++s;
      } else ++f;
    }
  }
  return 0;
}
