#include <iostream>

int main() {
  int n, m;
  std::cin >> n >> m;
  unsigned long long a;
  std::cin >> a; // ignore zero argument;
  std::cin >> a;
  unsigned long long sum = a % 2;
  bool isFirstOdd = sum == 1;
  bool isAllZero = a == 0;
  unsigned long long sum2 = 0;
  for(int i = 2; i <= n; ++i) {
    std::cin >> a;
    sum = (sum + a) % 2;
    isAllZero = isAllZero && (a == 0);
    if((i % 2) == 0) sum2 = (sum2 + a) % 2;
  }
  bool isSumEven = sum == 0;
  bool isSum2Even = sum2 == 0;
  if(m == 1) {
    std::cout << (!isAllZero && isSumEven ? "No" : "Yes") << std::endl;
  } else {
    std::cout << (isFirstOdd && isSum2Even ? "No" : "Yes") << std::endl;
  }
}
