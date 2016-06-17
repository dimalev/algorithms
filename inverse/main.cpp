#include <iostream>
#include <set>

std::set<long> testing;

long inv(long x, long P) {
  if(x == 1) return 1;
  if(testing.find(x) != testing.end()) {
    std::cout << "Error while counting " << x << std::endl;
    return 0;
  }
  testing.insert(x);
  long i = inv(P % x, P);
  testing.erase(x);
  return P - ((P / x) * i) % P;
}

int main() {
  long P = 1000000007L;
  long x = 1000000006L;
  long invX = inv(x, P);

  std::cout << invX << " " << (x * invX) % P << std::endl;
  return 0;
}
