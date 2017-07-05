#include <iostream>

int main() {
  int N = 1e5;
  std::cout << "1\n";
  std::cout << N << "\n";
  for(int i = 0; i < N; ++i) {
    if(i > 0) std::cout << " ";
    if(i == 150 || i == 2200 || i == 17556 || i == 5684)
      std::cout << "1";
    else std::cout << (1e5 - i % 2);
  }
}
