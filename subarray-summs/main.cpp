#include <iostream>

int main() {
  int T;
  std::cin >> T;
  while(T--) {
    int N;
    std::cin >> N;

    if(N % 2 == 0) {
      for(int i = 0; i < N; ++i) {
        int z;
        std::cin >> z;
      }
      std::cout << 0 << std::endl;
    } else {
      int total = 0;
      for(int i = 0; i < N; ++i) {
        int z;
        std::cin >> z;
        if(i % 2 == 0) total ^= z;
      }
      std::cout << total << std::endl;
    }
  }
}
