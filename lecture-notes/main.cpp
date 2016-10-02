#include <iostream>

int main() {
  int n, k;
  std::cin >> n >> k;
  char line[n];
  std::cin >> line;
  for(int i = 0; i < k; ++i) {
    int z;
    std::cin >> z;
    if(line[z] == '1') {
      std::cout << "YES" << std::endl;
      return 0;
    }
  }
  std::cout << "NO" << std::endl;
}
