#include <iostream>
#include <algorithm>
#include <list>
#include <vector>
#include <set>

const int limit = 75000;

int zeroes[262144];
int all[262144];
int histo[limit];
int data[limit];

int maxX = 0;

inline int mid(int l, int r) { return (l + r) / 2; }

inline int left(int id) { return 2 * id + 1; }
inline int right(int id) { return 2 * (id + 1); }

inline int max(int a, int b) { return a > b ? a : b; }
inline int min(int a, int b) { return a > b ? b : a; }

void setup(int id, int l, int r) {
  if(id > maxX) maxX = id;
  if(l == r) {
    all[id] = histo[r];
    zeroes[id] = 1 ^ histo[r];
    // std::cout << id << ": " << l << " -> " << r << " = " << ones[id] << std::endl;
    return;
  }
  setup(left(id), l, mid(l, r));
  setup(right(id), mid(l, r) + 1, r);
  zeroes[id] = zeroes[left(id)] + zeroes[right(id)];
  all[id] = -1;
  // std::cout << id << ": " << l << " -> " << r << " = " << ones[id] << std::endl;
}

int getNodeCount(int id, int l, int r) {
  if(all[id] == -1) return zeroes[id];
  return all[id] == 0 ? r - l + 1 : 0;
}

void push(int id) {
  if(all[id] == -1) return;
  all[right(id)] = all[left(id)] = all[id];
  all[id] = -1;
}

int count(int id, int l, int r, int ll, int rr) {
  if(r < ll || rr < l) return 0;
  if(ll <= l && r <= rr) return getNodeCount(id, l, r);
  push(id);
  return count(left(id), l, mid(l, r), ll, rr) + count(right(id), mid(l, r) + 1, r, ll, rr);
}

void update(int id, int l, int r, int ll, int mm, int rr) {
  if(r < ll || rr < l) return;
  if(l >= ll && r < mm) {
    all[id] = 0;
    return;
  }
  if(l >= mm && r <= rr) {
    all[id] = 1;
    return;
  }
  // std::cout << "update: " << id << " (" << l << ", " << r << ") ";
  // std::cout << "[" << ll << ":" << mm << ":" << rr << "]" << std::endl;
  if(l == r) {
    all[id] = l < mm ? 0 : 1;
    zeroes[id] = l < mm ? 1 : 0;
    return;
  }
  push(id);
  update(left(id), l, mid(l, r), ll, mm, rr);
  update(right(id), mid(l, r) + 1, r, ll, mm, rr);
  zeroes[id] = getNodeCount(left(id), l, mid(l, r)) + getNodeCount(right(id), mid(l, r) + 1, r);
}

int main() {
  int n, q, k;
  std::cin >> n >> q >> k;
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

  int L[q], R[q];
  for(int i = 0; i < q; ++i)
    std::cin >> L[i] >> R[i];

  int l = -1, r = n;
  while(r - l > 1) {
    int m = (l + r) / 2;
    for(int i = 0; i < n; ++i) histo[i] = data[i] > m ? 1 : 0;
    setup(0, 0, n - 1);
    for(int i = 0; i < q; ++i) {
      int countZero = count(0, 0, n - 1, L[i], R[i]);
      update(0, 0, n - 1, L[i], L[i] + countZero, R[i]);
    }
    int z = count(0, 0, n - 1, k, k);
    if(z == 0) l = m; else r = m;
  }

  std::cout << vocabulary[r] << std::endl;
}
