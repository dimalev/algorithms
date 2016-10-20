#include <iostream>
#include <cstring>
#include <algorithm>

constexpr int MAX_N = 3000;

int longest_palyndrome(char * const line, int N) {
  int *scanline = new int[MAX_N];
  int *next_scanline = new int[MAX_N];
  std::memset(scanline, 0, MAX_N);
  for(int i = 0; i < N; ++i) {
    next_scanline[0] = line[N - i - 1] == line[0] ? 1 : 0;
    for(int j = 1; j < N; ++j) {
      if(line[N - i - 1] == line[j]) {
        next_scanline[j] = scanline[j - 1] + 1;
      } else next_scanline[j] = std::max(next_scanline[j - 1], scanline[j]);
    }
    std::swap(scanline, next_scanline);
  }
  return scanline[N - 1];
}

int main() {
  int T;
  std::cin >> T;
  for (int t = 0; t < T; ++t) {
    int N, K, out = 0;
    char line[MAX_N + 1], another[MAX_N + 2];
    std::cin >> N >> K;
    std::cin >> line;
    int max = longest_palyndrome(line, N);
    for(int i = 0; i <= N; ++i) {
      std::memcpy(another, line, i);
      std::memcpy(another + i + 1, line + i, N - i);
      another[N + 2] = 0;
      bool is_first = true;
      for(char c = 'a'; c <= 'z'; ++c) {
        another[i] = c;
        int new_max = longest_palyndrome(another, N + 1);
        if(new_max >= max + K) {
          if(is_first) std::cout << "---" << std::endl;
          std::cout << another << std::endl;
          ++out;
          is_first = false;
        }
      }
    }
    std::cout << out << std::endl;
  }
}
