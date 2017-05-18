#include <iostream>
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

inline int val(char C) {
  switch(C) {
    case 'G': return 0;
    case 'T': return 1;
    case 'C': return 2;
    case 'A': return 3;
  }
  return -1;
}

int main() {
  UNIT_TESTS();
  int hysto[4][500000];
  int n;
  std::cin >> n;
  char buffer[1000];
  int step = 0;
  buffer[0] = '\0';
  for(int i = 0; i < n; ++i) {
    if(buffer[i - step] == '\0') {
      step = i;
      scanf("%999s", buffer);
    }
    char C = buffer[i - step];
    int V = val(C);
    if(i > 0) {
      for(int j = 0; j < 4; ++j)
        hysto[j][i] = hysto[j][i - 1];
    } else {
      for(int j = 0; j < 4; ++j)
        hysto[j][i] = 0;
    }
    hysto[V][i]++;
  }
  int l = 0, r = n - 1;
  int m = n / 4;
  int best = n;
  for(int l = 0; l < n; ++l) {
    bool is_good = true;
    r = std::min(r + 1, n - 1);
    while(is_good && r >= l) {
      for(int i = 0; i < 4; ++i) {
        int s = 0;
        if(l > 0) s += hysto[i][l - 1];
        s += hysto[i][n - 1] - hysto[i][r];
        if(s > m) {
          is_good = false;
          break;
        }
      }
      if(is_good) {
        best = r - l + 1;
        --r;
      }
    }
    if(r < l && is_good) {
      best = 0;
      break;
    }
  }
  std::cout << best << std::endl;
  return 0;
}
