#include <iostream>
#include <algorithm>

class dish {
public:
  long p, d;
  static bool by_dp(const dish &left, const dish &right) {
    return left.p + left.d > right.p  + right.d;
  }
};

int main() {
  long n, k;
  std::cin >> n >> k;
  dish all[n];
  for(int i = 0; i < n; ++i) {
    std::cin >> all[i].p >> all[i].d;
  }
  std::sort(all, all + n, dish::by_dp);
  unsigned long long summ = 0;
  for(int i = 0; i < n; ++i) {
    if(i < k) summ += all[i].p;
    else {
      if(summ < all[i].d) {
        std::cout << 0 << std::endl;
        return 0;
      }
      summ -= all[i].d;
    }
  }
  std::cout << summ << std::endl;
  return 0;
}
