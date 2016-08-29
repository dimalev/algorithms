#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cstring>

const int N_MAX = 100000;

std::vector<int> links[N_MAX];
int n, m, p[N_MAX];
int x;

bool used[N_MAX];
int arity[N_MAX];

void read() {
  std::cin >> n >> m;
  std::memset(arity, 0, sizeof(int) * n);
  std::memset(used, false, sizeof(bool) * n);
  for(int i = 0; i < m; ++i) {
    int u, v;
    std::cin >> u >> v;
    links[u - 1].push_back(v - 1);
    arity[v - 1]++;
  }
  for(int i = 0; i < n; ++i) {
    int pp;
    std::cin >> pp;
    p[i] = pp - 1;
  }
}

void findFirstReplacable() {
  std::set<int> free;
  bool used[n];
  int best = p[n - 1];
  std::memset(used, false, n * sizeof(bool));
  free.insert(p[n - 1]);
  used[p[n - 1]] = true;
  for(int i = n - 2; i >= 0; --i) {
    for(int v : links[p[i]]) {
      if(used[v]) {
        free.erase(v);
        if(best == v) best = -1;
        used[v] = false;
      }
    }
    if(best == -1) best = *std::max_element(free.begin(), free.end());
    if(free.size() == 0 || best < p[i]) {
      free.insert(p[i]);
      used[p[i]] = true;
      if(p[i] > best) best = p[i];
      continue;
    }
    for(int k : free) if(k > p[i] && k < best) best = k;
    int best_ind;
    for(int k = i + 1; k < n; ++k)
      if(p[k] == best) {
        best_ind = k;
        break;
      }
    p[best_ind] = p[i];
    p[i] = best;
    x = i;
    return;
  }
  x = -1;
}

void sortTail() {
  for(int i = 0; i <= x; ++i) {
    for(int v : links[p[i]]) arity[v]--;
  }
  std::vector<int> zero;
  for(int i = x + 1; i < n; ++i) {
    if(arity[p[i]] == 0) zero.push_back(p[i]);
  }
  std::make_heap(zero.begin(), zero.end(), std::greater<int>());
  for(int z = x + 1; z < n; ++z) {
    int best = zero.front();
    std::pop_heap(zero.begin(), zero.end(), std::greater<int>()); zero.pop_back();
    p[z] = best;
    for(int v : links[best]) {
      if(--arity[v] == 0) {
        zero.push_back(v);
        std::push_heap(zero.begin(), zero.end(), std::greater<int>());
      }
    }
  }
}

void write() {
  std::cout << (p[0] + 1);
  for(int i = 1; i < n; ++i) std::cout << " " << (p[i] + 1);
  std::cout << std::endl;
}

int main() {
  read();
  findFirstReplacable();
  if(x < 0) {
    std::cout << -1 << std::endl;
    return 0;
  }
  sortTail();
  write();
  return 0;
}
