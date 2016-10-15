// get number, find sqrt, frint error if bad number
#include <iostream>
#include <cmath>

int main() {
  int i;
  std::cout << "Enter number to sqrt: ";
  std::cin >> i;
  int q = std::sqrt(i);
  if(errno != 0) {
    std::cout << "Errno is not zero" << std::endl;
    return 0;
  }
  std::cout << q << std::endl;
  return 0;
}
