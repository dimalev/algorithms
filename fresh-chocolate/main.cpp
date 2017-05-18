#include <iostream>
#include <algorithm>

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

void solve(int t) {
  int N, P;
  std::cin >> N >> P;
  int leftovers[P];
  std::fill_n(leftovers, P, 0);
  int complete = 0;
  for(int i = 0; i < N; ++i) {
    int g;
    std::cin >> g;
    if(g % P == 0) {
      ++complete;
    } else if(leftovers[P - g % P] > 0){
      --leftovers[P - g % P];
      ++complete;
    } else {
      leftovers[g % P]++;
    }
  }
  if(P == 2) {
    complete += (leftovers[1] % 2);
  }
  if(P == 3) {
    complete += (leftovers[1] / 3) + (std::min(leftovers[1] % 3, 1));
    complete += (leftovers[2] / 3) + (std::min(leftovers[2] % 3, 1));
  }
  else if(P == 4) {
    if(leftovers[2] == 1) {
      if(leftovers[1] > 2) {
        ++complete;
        leftovers[1] -= 2;
      } else if(leftovers[3] > 2) {
        ++complete;
        leftovers[3] -= 2;
      } else {
        if(leftovers[1] == 0 && leftovers[3] == 0) {
          ++complete;
        }
      }
    }
    complete += (leftovers[1] / 4) + (std::min(leftovers[1] % 4, 1));
    complete += (leftovers[3] / 4) + (std::min(leftovers[3] % 4, 1));
  }
  std::cout << "Case #" << t << ": " << complete << "\n";
}

int main() {
  UNIT_TESTS();
  int T;
  std::cin >> T;
  for(int t = 1; t <= T; ++t) solve(t);
  return 0;
}
