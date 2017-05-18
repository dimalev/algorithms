#include <iostream>
#include <set>
#include <algorithm>

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else

#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)
#define UNIT_TESTS()

#endif

void unit_tests() {
}

int main() {
  UNIT_TESTS();
  int n, m;
  std::cin >> n >> m;
  int groups[200000], k = 0;
  int hates[200000][2];
  std::fill_n(groups, n, -1);
  for(int i = 0; i < m; ++i) {
    std::cin >> hates[i][0] >> hates[i][1];
    --hates[i][0]; --hates[i][1];
  }
  std::set<int> ppl;
  for(int i = 0; i < n; ++i) ppl.insert(i);
  while(!ppl.empty()) {
    int f = *ppl.begin();
    groups[f] = k;
    std::set<int> notmark;
    for(int j = 0; j < m; ++j) {
      if(hates[j][0] == f) {
        notmark.insert(hates[j][1]);
      } else if(hates[j][1] == f) {
        notmark.insert(hates[j][0]);
      }
    }
    std::set<int> mark;
    for(int s : ppl) {
      if(notmark.find(s) == notmark.end()) {
        mark.insert(s);
        groups[s] = k;
      }
    }
    for(int s : mark) ppl.erase(ppl.find(s));
    ++k;
  }
  std::cout << k << "\n";
  std::cout << (groups[0] + 1);
  for(int i = 1; i < n; ++i) {
    std::cout << " " << (groups[i] + 1);
  }
  std::cout << std::endl;
  return 0;
}
