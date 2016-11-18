#include <iostream>

int main() {
  int n, q;
  std::cin >> n >> q;
  std::cout << n << " " << q << std::endl;
  constexpr int M = 3;
  for(int i = 0; i < n; ++i) {
    std::cout << (i * M) << " " << (-i * M) << " "
              << ((i + 1) * M) << " " << (-i * M - 3 * M) << std::endl;
  }
  for(int i = 0; i < q; ++i) {
    std::cout << (i * M + 2) << " " << (-i * M) << std::endl;
  }
}
