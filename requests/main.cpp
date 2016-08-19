#include <iostream>
#include <algorithm>
#include <list>
#include <vector>
#include <set>

const int limit = 75000;

int ones[2 * limit];
int histo[limit];
int data[limit];

inline int mid(int l, int r) { return (l + r) / 2; }

inline int left(int id) { return 2 * id + 1; }
inline int right(int id) { return 2 * (id + 1); }

inline int max(int a, int b) { return a > b ? a : b; }
inline int min(int a, int b) { return a > b ? b : a; }

void setup(int id, int l, int r) {
  if(l == r) {
    ones[id] = histo[r];
    return;
  }
  setup(left(id), l, mid(l, r));
  setup(right(id), mid(l, r) + 1, r);
  ones[id] = ones[left(l, r)] + ones[right(l, r)];
}

int count(int id, int l, int r, int ll, int rr) {
  if(r < ll || rr < l) return 0;
  if(ll <= l && rr >= r) return ones[id];
  return count(left(id), l, mid(l, r), ll, rr) + count(right(id), mid(l, r) + 1, r, ll, rr);
}

void update(int id, int l, int r, int ll, int mm, int rr) {
  if(l == r) {
    if(l <= mm) ones[id] = 1;
    else ones[id] = 0;
  }
  update(left(id), l, mid(l, r), ll, mm, rr);
  update(right(id), mid(l, r) + 1, r, ll, mm, rr);
  ones[id] = ones[left(id)] + ones[right(id)];
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

  int l = -1, r = n - 1;
  while(r - l > 1) {
    int m = (l + r + 1) / 2;
    int el = vocabulary[m];
    for(int i = 0; i < n; ++i) histo[i] = data[i] >= el;
    setup(0, 0, n - 1);
    for(int i = 0; i < q; ++i) {
      /*
        update predicate data
      */
    }
    if(pred[k]) l = m; else r = m;
  }

  std::cout << vocabulary[r] << std::endl;
}
