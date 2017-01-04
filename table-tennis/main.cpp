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

std::array<std::array<double, MAX_N>, MAX_N> p;

double count(const std::set<unsigned int> &winners) {
  if(winners.size() == N - 1) return 1.0;
  double total = 0.0;
  for(unsigned int i = 0; i < N; ++i) {
    if(winners.find(i) != winners.end()) continue;
    double win_rate = 1.0;
    for(unsigned int j = 0; j < N; ++j)
      if(i != j && winners.find(j) == winners.end())
        win_rate *= p[i][j];
    std::set<unsigned int> new_winners{winners};
    new_winners.emplace(i);
    total += win_rate * count(new_winners);
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
  std::cout << std::fixed << std::setprecision(15) << count({});
  return 0;
}
