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

int main() {
  UNIT_TESTS();
  int n, a, b;
  std::cin >> n >> a >> b;
  int T[n], unread = 0;
  int time = 0, oldest = -1;
  for(int i = 0; i < n; ++i) {
    std::cin >> T[i];
    if(oldest == -1) oldest = T[i];
    time = T[i];
    while(time - oldest > b) {
      int btime = time;
      time = oldest + b;
      --i;
      int K = (i - unread + 1) / 2 + (i - unread + 1) % 2;
      for(int j = unread; j < unread + K; ++j) {
        if(j < n - 1)
          std::cout << time << " ";
        else std::cout << time << "\n";
      }
      unread += K;
      ++i;
      time = btime;
      oldest = T[unread];
    }
    if(i - unread + 1 >= a) {
      int K = (i - unread + 1) / 2 + (i - unread + 1) % 2;
      for(int j = unread; j < unread + K; ++j) {
        if(j < n - 1)
          std::cout << time << " ";
        else std::cout << time << "\n";
      }
      unread += K;
      oldest = T[unread];
    }
  }
  while(unread < n) {
    time = T[unread] + b;
    int K = (n - unread) / 2 + (n - unread) % 2;
    for(int j = unread; j < unread + K; ++j) {
      if(j < n - 1)
        std::cout << time << " ";
      else std::cout << time << "\n";
    }
    unread += K;
  }
  return 0;
}
