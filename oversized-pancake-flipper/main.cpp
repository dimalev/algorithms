#include <iostream>
#include <algorithm>
#include <list>
#include <string>

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else

#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)
#define UNIT_TESTS()

#endif

void solve(int T) {
  std::string config;
  int K;
  std::cin >> config >> K;
  std::list<bool> current_flip(K);
  std::fill(current_flip.begin(), current_flip.end(), false);
  int flips = 0;
  for(int i = 0, len = config.length(); i < len; ++i) {
    bool is_happy = config[i] == '+';
    bool is_flipped = current_flip.front();
    current_flip.pop_front();
    if(is_happy == is_flipped) {
      if(i > len - K) {
        std::cout << "Case #" << T << ": IMPOSSIBLE\n";
        return;
      }
      ++flips;
      auto iterator = current_flip.begin();
      while(iterator != current_flip.end()) {
        *iterator = !(*iterator);
        ++iterator;
      }
    }
    current_flip.push_back(false);
  }
  std::cout << "Case #" << T << ": " << flips << "\n";
}

void unit_tests() {
}

int main() {
  UNIT_TESTS();
  int N;
  std::cin >> N;
  for(int i = 1; i <= N; ++i) {
    solve(i);
  }
  return 0;
}
