#include <iostream>
#include <cstring>

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else

#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)

#endif

const int MAX_S = 100006;

char line[MAX_S];

/*

0123
abac

*/

bool first_wrong(int left, int right, int &padding) {
  int max_padding = (right - left) / 2 + ((right - left) % 2);
  for(int i = 0; i < max_padding; ++i) {
    if(line[left + i] != line[right - i]) {
      padding = i;
      return true;
    }
  }
  return false;
}

int main() {
  int T;
  std::cin >> T;
  for(int t = 0; t < T; ++t) {
    std::cin >> line;
    int wrong_index;
    int S = std::strlen(line);
    if(first_wrong(0, S - 1, wrong_index)) {
      int next_wrong;
      if(first_wrong(wrong_index + 1, S - wrong_index - 1, next_wrong)) {
        std::cout << S - wrong_index - 1 << std::endl;
      } else std::cout << wrong_index << std::endl;
    } else std::cout << -1 << std::endl;
  }
  return 0;
}
