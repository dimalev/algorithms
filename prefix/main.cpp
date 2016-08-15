#include <iostream>

int main() {
  int q, n = 0, vals[200000], prev[200000];
  prev[0] = -1;
  std::cin >> q;
  for(int i = 0; i < q; ++i) {
    char op;
    std::cin >> op;
    if(op == '+') {
      int v;
      std::cin >> v;
      vals[n] = v;
      if(n > 0) {
        int p = prev[n - 1];
        while(p >= 0) {
          if(vals[p + 1] == v) break;
          p = prev[p];
        }
        if(p >= 0) prev[n] = p + 1;
        else prev[n] = vals[0] == vals[n] ? 0 : -1;
      }
      std::cout << (prev[n] + 1) << std::endl;
      ++n;
    } else {
      --n;
      std::cout << (n > 0 ? prev[n - 1] + 1 : 0) << std::endl;
    }
  }
  return 0;
}
