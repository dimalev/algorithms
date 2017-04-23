#include <iostream>
#include <iomanip>
#include <map>

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else

#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)
#define UNIT_TESTS()

#endif

void solve(int t) {
  double D;
  int N;
  std::cin >> D >> N;
  std::map<double, double> horses;
  for(int i = 0; i < N; ++i) {
    double K, S;
    std::cin >> K >> S;
    horses[K] = S;
  }
  std::cout << std::setprecision(8);
  auto it = horses.rbegin();
  bool is_first = true;
  double limit = 0.0f;
  while(it != horses.rend()) {
    double time = (D - it->first) / it->second;
    if(is_first) {
      limit = time;
      is_first = false;
    } else {
      if(time > limit) {
        limit = time;
      }
    }
    ++it;
  }
  std::cout << "Case #" << t << ": " << (D / limit) << std::endl;
}

void unit_tests() {
}

int main() {
  UNIT_TESTS();
  int T;
  std::cin >> T;
  for(int t = 1; t <= T; ++t) solve(t);
  return 0;
}
