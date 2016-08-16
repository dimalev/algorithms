#include <iostream>
#include <algorithm>
#include <list>
#include <vector>
#include <set>

const int limit = 75000;

int main() {
  int n, q, k;
  std::cin >> n >> q >> k;
  long data[n];
  std::set<int> unique;
  for(int i = 0; i < n; ++i) {
    std::cin >> data[i];
    unique.insert(data[i]);
  }
  int uniq_count = unique.size();
  long vocabulary[uniq_count];
  int j = 0;
  for(int i : unique) {
    vocabulary[j++] = i;
  }
  std::sort(vocabulary, vocabulary + uniq_count);

  std::transform(data, data + n, data, [&](int item) -> int { return std::lower_bound(vocabulary, vocabulary + uniq_count, item) - vocabulary; });

  int L[n], R[n];
  for(int i = 0; i < q; ++i)
    std::cin >> L[i] >> R[i];

  int l = 0, r = n;
  while(l < r - 1) {
    int m = (l + r + 1) / 2;
    long el = data[m];
    bool pred[n];
    // std::cout << m << " " << vocabulary[data[m]] << ":";
    std::transform(data, data + n, pred, [&](int item) -> bool { return item <= el; });
    // for(int i = 0; i < n; ++i) std::cout << " " << (pred[i] ? 1 : 0);
    for(int i = 0; i < q; ++i) {
      int ones = std::count(pred + L[i], pred + R[i] + 1, true);
      for(int j = 0; j < ones; ++j) pred[L[i] + j] = true;
      for(int j = ones; j <= R[i] - L[i]; ++j) pred[L[i] + j] = false;
      // std::cout << " |";
      // for(int j = 0; j < n; ++j) std::cout << " " << (pred[j] ? 1 : 0);
    }
    // std::cout << " |";
    // for(int i = 0; i < n; ++i) std::cout << " " << (pred[i] ? 1 : 0);
    // std::cout << std::endl;
    if(pred[k]) l = m; else r = m;
  }

  std::cout << vocabulary[data[l]] << std::endl;
}
