#include <iostream>
#include <cmath>

int main() {
  int i;
  std::cin >> i;
  int q = std::sqrt(i);
  if(errno != 0) {
    std::cout << "Errno is not zero" << std::endl;
    return 0;
  }
  std::cout << q << std::endl;
  return 0;
}
