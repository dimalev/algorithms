#include <iostream>
#include <vector>
#include <algorithm>

const int N_MAX = 100000;

std::vector<int> links[N_MAX];
int n, m, p[N_MAX];
int x;

void read() {
  std::cin >> n >> m;
  for(int i = 0; i < m; ++i) {
    int u, v;
    std::cin >> u >> v;
    links[u - 1].push_back(v - 1);
  }
  for(int i = 0; i < n; ++i) {
    int pp;
    std::cin >> pp;
    p[i] = pp - 1;
  }
}

void findFirstReplacable() {
  std::vector<std::pair<int, int>> free;
  free.push_back(std::pair<int, int>(p[n - 1], n - 1));
  std::sort(links[p[n - 1]].begin(), links[p[n - 1]].end());
  for(int i = n - 2; i >= 0; --i) {
    std::sort(links[p[i]].begin(), links[p[i]].end());
    auto free_end = std::remove_if(free.begin(), free.end(), [&](std::pair<int, int> pp) -> bool {
        return std::binary_search(links[p[i]].begin(), links[p[i]].end(), pp.first);
      });
    if(free_end != free.end()) free.resize(std::distance(free.begin(), free_end));
    std::sort(free.begin(), free.end(), [](std::pair<int, int> left, std::pair<int, int> right) -> bool {
        return right.first < left.first;
      });
    int sz = free.size();
    // std::cout << (p[i] + 1) << ":";
    // for(int j = 0; j < sz; ++j) std::cout << " " << (free[j].first + 1);
    // std::cout << std::endl;
    if(sz == 0 || free[0].first < p[i]) {
      free.push_back(std::pair<int, int>(p[i], i));
      continue;
    }
    int k = 0;
    while(k < sz - 1 && free[k + 1].first > p[i]) ++k;
    int free_vert = free[k].first;
    int free_id = free[k].second;
    // std::cout << free_id << " = " << (free_vert + 1) << std::endl;
    for(int j = free_id; j > i; --j) p[j] = p[j - 1];
    p[i] = free_vert;
    x = i;
    return;
  }
  x = -1;
}

void sortTail() {
  for(int i = n - 2; i > x; --i) {
    int j = i + 1;
    while(j < n && p[j] < p[j - 1]) {
      if(std::binary_search(links[p[j - 1]].begin(), links[p[j - 1]].end(), p[j])) break;
      int t = p[j];
      p[j] = p[j - 1];
      p[j - 1] = t;
      ++j;
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
