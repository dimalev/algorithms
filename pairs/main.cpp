#include <iostream>
#include <list>
#include <cmath>

typedef unsigned long long ull;

const ull MOD = 1000000007LL;

inline ull max(ull a, ull b) { return a > b ? a : b; }
inline ull min(ull a, ull b) { return a < b ? a : b; }

ull f(ull n, ull m) {
  ull res = 1;
  for(ull x = n + 1; x <= m; ++x) res = (res * x) % MOD;
  return res;
}

ull f(ull n) {
  return f(1, n);
}

inline ull floor2(ull n) { return n / 2LL; }
inline ull ceil2(ull n) { return n / 2LL + n % 2LL; }

ull gcd(ull X, ull Y) {
  ull top = min(X, Y) / 2LL;
  ull res = 1LL;
  for(ull m = 2LL; m <= top; m == 2 ? ++m : m += 2) {
    while(X % m == 0 && Y % m == 0) {
      X = X / m;
      Y = Y / m;
      res *= m;
    }
  }
  return res;
}

ull comb(ull N, ull M) {
  ull top = N;//f(M, N);
  ull bot = M;//f(N - M);
  if(top % bot == 0)
    return (top / bot) % MOD;
  // ull g = gcd(top, bot);
  // top /= g;
  // bot /= g;
  for(ull x = top / bot; x < MOD; ++x)
    if(x * bot % MOD == top) return x;
}

int main() {
  std::cout << comb(666666666, 999999999) << std::endl;
  // ull w, m, p;
  // std::cin >> w >> m >> p;
  // // std::list<ull> res;
  // if(p == 0) {
  //   std::cout << f(max(w, m));
  //   return 0;
  // }
  // ull res = 0;
  // for(ull pi = 1; pi <= p; ++pi) {
  //   res = (res + ((f(pi) * f(w - pi) % MOD) * f(m - pi) % MOD) * ( // permutations of all M
  //     // (M) MW (W) WM (M) <- ceil2 for M
  //     comb(w - pi + floor2(pi - 1), floor2(pi - 1)) *
  //     comb(m - pi + ceil2(pi - 1), ceil2(pi - 1)) % MOD +
  //     // (W) WM (M) MW (W) <- ceil2 for W
  //     comb(w - pi + ceil2(pi - 1), ceil2(pi - 1)) *
  //     comb(m - pi + floor2(pi - 1), floor2(pi - 1) % MOD)
  //   )) % MOD;
  // }
  // std::cout << res;
  return 0;
}

//  (M)  MW  (W)  WM (M) MW (W) WM (M)
//  01234

// 3 M 3 W 2 P

// MWWM -> MM
