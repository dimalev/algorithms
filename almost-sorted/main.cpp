#include <iostream>
#include <algorithm>
#include <vector>

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

std::vector<std::pair<int, int>> find_falls(const int *d, const int &N) {
  std::vector<std::pair<int, int>> result;
  int start = 0, element = d[0], end = 0;
  for(int i = 1; i < N; ++i) {
    if(d[i] < element) {
      end = i;
    } else {
      if(start < end) {
        result.push_back(std::make_pair(start, end));
      }
      start = end = i;
    }
    element = d[i];
  }
  if(start < end) {
    result.push_back(std::make_pair(start, end));
  }
  return result;
}

int main() {
#ifdef UNITS
  unit_tests();
  return 0;
#endif
  int N, *d = new int[100000];
  std::cin >> N;
  for(int i = 0; i < N; ++i) std::cin >> d[i];
  std::vector<std::pair<int, int>> reverses = find_falls(d, N);
  if(reverses.empty()) {
    std::cout << "yes" << std::endl;
  } else if(reverses.size() == 1) {
    std::pair<int, int> single = reverses[0];
    if(single.second - single.first == 1) {
      std::swap(d[single.second], d[single.first]);
      reverses = find_falls(d, N);
      if(reverses.empty()) {
        std::cout << "yes" << std::endl;
        std::cout << "swap " << (single.first + 1) << " " << (single.second + 1)
                  << std::endl;
      } else {
        std::cout << "no\n";
      }
    } else {
      std::reverse(d + single.first, d + single.second + 1);
      reverses = find_falls(d, N);
      if(reverses.empty()) {
        std::cout << "yes" << std::endl;
        std::cout << "reverse " << (single.first + 1) << " "
                  << (single.second + 1) << std::endl;
      } else {
        std::cout << "no\n";
      }
    }
  } else if(reverses.size() == 2) {
    std::pair<int, int> one = reverses[0], two = reverses[1];
    if(one.second - one.first == 1 && two.second - two.first == 1) {
      std::swap(d[one.first], d[two.second]);
      reverses = find_falls(d, N);
      if(reverses.empty()) {
        std::cout << "yes" << std::endl;
        std::cout << "swap " << (one.first + 1) << " " << (two.second + 1)
                  << std::endl;
      } else {
        std::cout << "no\n";
      }
    }
  } else {
    std::cout << "no\n";
  }
  delete[] d;
  return 0;
}
