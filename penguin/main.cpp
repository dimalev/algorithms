#include <iostream>
#include <limits>

typedef long ul;

int main() {
  ul N;
  ul posMin = std::numeric_limits<ul>::min();
  ul negMax = std::numeric_limits<ul>::max();
  std::cin >> N;
  while(N--) {
    int x;
    char d;
    std::cin >> x >> d;
    if(d == '-' && x < negMax) negMax = x;
    else if(d == '+' && x > posMin) posMin = x;
  }
  // std::cout << negMax << " " << posMin << std::endl;
  if(negMax >= posMin) std::cout << 1 << std::endl;
  else std::cout << 2 << std::endl;
}
