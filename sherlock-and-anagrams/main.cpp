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

constexpr int MAX_S = 101;
constexpr int CHARS = 26;
constexpr int CHARS_SIZE = CHARS * sizeof(int);

int S;
char line_origin[MAX_S];
int line[MAX_S];
int original_histo[CHARS];
int duple_histo[CHARS];

int find_same(int start, int length) {
  int total = 0;
  for(int i = start; i <= S - length; ++i) {
    bool is_same = true;
    std::memcpy(duple_histo, original_histo, CHARS_SIZE);
    for(int j = 0; j < length; ++j) {
      if(duple_histo[line[i + j]] == 0) {
        is_same = false;
        break;
      }
      --duple_histo[line[i + j]];
    }
    if(is_same) total += (i == start ? 1 : 2);
  }
  return total;
}

void countup(int start, int length) {
  std::memset(original_histo, 0, CHARS_SIZE);
  for(int j = 0; j < length; ++j) ++original_histo[line[start + j]];
}

int main() {
  int T;
  std::cin >> T;
  for(int t = 0; t < T; ++t) {
    std::cin >> line_origin;
    S = std::strlen(line_origin);
    std::transform(line_origin, line_origin + S, line, [](char &c) -> int { return c - 'a'; });
    int S2 = S / 2;
    int total = 0;
    for(int length = 1; length <= S2; ++length) {
      int end = S - 2 * length;
      for(int start = 0; start <= end; ++start) {
        countup(start, length);
        total += find_same(start + length, length);
      }
    }
    std::cout << total << std::endl;
  }
  return 0;
}
