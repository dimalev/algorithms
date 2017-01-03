#include <iostream>
#include <limits>
#include <cmath>

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
  double V, N;
  double T;
  std::cin >> V >> T;
  std::cin >> N;
  int L;
  double t;
  std::cin >> L >> t;
  int minI = 1;
  double minT = L + V * (t + T);
  for(int i = 2; i <= N; ++i) {
    std::cin >> L >> t;
    double totalT = L + V * (t + T);
    if(totalT < minT) {
      minT = totalT;
      minI = i;
    }
  }
  std::cout.precision(5);
  std::cout.setf ( std::ios::fixed, std::ios::floatfield );
  std::cout << minT << " " << minI;
  return 0;
}
