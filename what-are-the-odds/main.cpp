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

constexpr int N_MAX = 5 * 1e5;

int main() {
  UNIT_TESTS();
  int N;
  bool evens[N_MAX], odds[N_MAX];
  evens[0] = odds[0] = true;
  bool isFirstEven;
  std::cin >> N;
  for(int i = 1; i < N + 1; ++i) {
    int s;
    std::cin >> s;
    if(s % 2 == 0) {
      evens[i] = !evens[i - 1];
      odds[i] = odds[i - 1];
    } else {
      evens[i] = evens[i - 1];
      odds[i] = !odds[i - 1];
    }
  }
  bool result = evens[N] == odds[N];
  int answer = 0;
  for(int i = 0; i < N; ++i) {
    for(int j = i; j < N; ++j) {
      if(((evens[i] == evens[j]) == (odds[i] == odds[j])) != result) ++answer;
    }
  }
  std::cout << answer << std::endl;
  return 0;
}
