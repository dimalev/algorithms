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

using ull = unsigned long long;

ull count_old(ull upto) {
  ull top = 3, res = 0;
  while(top < (1ll << 62) - 1ll) {
    bool stop = true;
    ull cutaway = 1;
    // std::cout << ":: " << top << std::endl;
    while(cutaway <= (top >> 1)) {
      if(top - cutaway <= upto) {
        // std::cout << (top - cutaway) << std::endl;
        ++res;
        stop = false;
      } // else std::cout << " - " << (top - cutaway) << std::endl;
      cutaway <<= 1;
    }
    if(stop) return res;
    top = (top << 1) + 1;
  }
  return 0;
}

int main() {
  UNIT_TESTS();
  ull from, to;
  std::cin >> from >> to;
  std::cout << count_old(to) - count_old(from - 1);
  return 0;
}
