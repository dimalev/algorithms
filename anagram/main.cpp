#include <iostream>
#include <cstring>
#include <algorithm>

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else

#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)

#endif

const int MAX_S = 10001;

char line[MAX_S];

int main() {
  int T;
  std::cin >> T;
  for(int t = 0; t < T; ++t) {
    std::cin >> line;
    int S = std::strlen(line);
    if(S % 2 == 1) {
      std::cout << -1 << std::endl;
      continue;
    }
    int histo[26];
    std::fill(histo, histo + 26, 0);
    int S2 = S / 2;
    for(int i = 0; i < S2; ++i) ++histo[line[i] - 'a'];
    for(int i = S2; i < S; ++i) --histo[line[i] - 'a'];
    int total = 0;
    for(int i = 0; i < 26; ++i) total += abs(histo[i]);
    std::cout << (total / 2) << std::endl;
  }
  return 0;
}
