#include <iostream>
#include <iomanip>
#include <array>
#include <set>

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else

#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)
#define UNIT_TESTS()

#endif

constexpr int MAX_N = 10;

unsigned int N;

std::array<bool, MAX_N> winners{false};
unsigned int winners_count = 0;

std::array<std::array<double, MAX_N>, MAX_N> p;

double count() {
  if(winners_count == N - 1) return 1.0;
  double total = 0.0;
  for(unsigned int i = 0; i < N; ++i) {
    if(winners[i]) continue;
    double win_rate = 1.0;
    for(unsigned int j = 0; j < N; ++j)
      if(i != j && !winners[j])
        win_rate *= p[i][j];
    winners[i] = true; ++winners_count;
    total += win_rate * count();
    winners[i] = false; --winners_count;
  }
  return total;
}

void unit_tests() {
}

int main() {
  UNIT_TESTS();
  std::cin >> N;
  for(unsigned int i = 0; i < N; ++i)
    for(unsigned int j = 0; j < N; ++j)
      std::cin >> p[i][j];
  std::cout << std::fixed << std::setprecision(15) << count();
  return 0;
}
