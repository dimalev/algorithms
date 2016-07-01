#include <iostream>
#include <cmath>

int main() {
  long n, k;
  std::cin >> n >> k;

  long first;
  std::cin >> first;
  long dd[100], c = 0L;
  long d = 2L;
  while(first > 1L && d <= std::sqrt(first)) {
    if(first % d == 0L) {
      dd[c++] = d;
      while(first % d == 0L) {
        first = first / d;
      }
    }
    d += (d == 2 ? 1 : 2);
  }
  if(first > 1L) {
    dd[c++] = first;
  }

  for(long i = 1L; i < n; ++i) {
    long num;
    std::cin >> num;
    long p = 0L;
    for(long j = 0L; j < c; ++j) {
      if(num % dd[j] == 0) {
        if(p < j)
          dd[p] = dd[j];
        ++p;
      }
    }
    c = p;
  }

  long newN = 0L;
  for(long i = 0L; i < c; ++i) {
    long newNewN = (k / dd[i]) * dd[i];
    if(newNewN > newN) newN = newNewN;
  }

  std::cout << newN << std::endl;
  return 0;
}
