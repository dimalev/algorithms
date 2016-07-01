#include <iostream>
#include <list>
#include <cmath>

typedef unsigned long long ull;

const ull MOD = 1000000007LL;

ull inv(ull x, ull P) {
  if(x == 1) return 1;
  ull i = inv(P % x, P);
  return P - ((P / x) * i) % P;
}

inline ull max(ull a, ull b) { return a > b ? a : b; }
inline ull min(ull a, ull b) { return a < b ? a : b; }

ull f(ull n, ull m) {
  ull res = 1LL;
  for(ull x = n + 1LL; x <= m; ++x) res = (res * x) % MOD;
  return res;
}

ull f(ull n) {
  return f(1LL, n);
}

ull g(ull m, ull t) {
  ull res = 1LL;
  for(ull i = 1LL; i <= m; ++i)
    res = res * (t + i) % MOD;
  return res;
}

int main() {
  ull w, m, p;
  std::cin >> m >> w >> p;
  if(p == 0) {
    std::cout << f(max(w, m));
    return 0;
  }
  ull res = 0LL;
  ull invF = 1LL;
  for(ull pi = 1LL; pi <= p; ++pi) {
    ull lres = 0LL;
    if(pi % 2LL == 0) {
      // std::cout << "even::" << std::endl;
      ull m1 = g(m - pi, pi / 2LL);
      ull m2 = g(m - pi, pi / 2LL - 1LL);
      ull w1 = g(w - pi, pi / 2LL - 1LL);
      ull w2 = g(w - pi, pi / 2LL);
      // std::cout << m1 << " " << w1 << std::endl;
      // std::cout << m2 << " " << w2 << std::endl;
      ull moreD = (f(pi) * m1 * w1 % MOD + f(pi) * m2 * w2 % MOD);
      // std::cout << pi << ": " << moreD << std::endl;
      // std::cout << "  M(" << m - pi << "): " << m1 << " " << m2 << std::endl;
      // std::cout << "  W(" << w - pi << "): " << w1 << " " << w2 << std::endl;
      lres = (lres + moreD) % MOD;
    } else {
      // std::cout << "odd::" << std::endl;
      ull mm = g(m - pi, (pi - 1LL) / 2LL);
      ull ww = g(w - pi, (pi - 1LL) / 2LL);
      // std::cout << mm << " " << ww << std::endl;
      ull moreD = (2LL * mm * ww) % MOD;
      lres = (lres + f(pi) * moreD) % MOD;
      // std::cout << pi << ": " << moreD << std::endl;
      // std::cout << "  M(" << m - pi << "): " << mm << std::endl;
      // std::cout << "  W(" << w - pi << "): " << ww << std::endl;
    }
    ull top = f(p - pi, p);
    invF = invF * inv(pi, MOD) % MOD;
    ull total = top * lres * invF % MOD;
    // std::cout << top << " * " << invF << " = " << (top * invF % MOD) << std::endl;
    // std::cout << lres << " " << res << " = " << total << std::endl;
    // std::cout << "--------------------" << std::endl;
    res = (res + total) % MOD;
  }
  std::cout << res << std::endl;
  return 0;
}

//  (M)  MW  (W)  WM (M) MW (W) WM (M)
//  01234

// 3 M 3 W 2 P

// MWWM -> MM
