#include <iostream>
#include <cstring>

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else

#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)
#define UNIT_TESTS()

#endif

class Mat {
 public:
  char* data;
  int R, C;

  Mat(int r, int c) : R{r}, C{c}, data{new char[r * (c + 1) + 1]} {
    data[r * (c + 1)] = '\0';
  }

  ~Mat() {
    delete[] data;
  }

  void whatever() {
    for(int i = 1; i < R; ++i) {
      char *rowptr = data + (i * (C + 1));
      char *prevrowptr = data + ((i - 1) * (C + 1));
      if(rowptr[0] == '?' && prevrowptr[0] != '?') {
        std::memcpy(rowptr, prevrowptr, C);
      }
    }
    for(int i = R -1; i >= 0; --i) {
      char *rowptr = data + (i * (C + 1));
      char *nextrowptr = data + ((i + 1) * (C + 1));
      if(rowptr[0] == '?' && nextrowptr[0] != '?') {
        std::memcpy(rowptr, nextrowptr, C);
      }
    }
  }

  void putline(int r, char *line) {
    char *rowptr = data + (r * (C + 1));
    std::memcpy(rowptr, line, C);
    rowptr[C] = '\n';
    char current = '?';
    for(int i = 0; i < C; ++i) {
      if(rowptr[i] != '?') {
        if(current == '?') {
          std::memset(rowptr, rowptr[i], i);
        }
        current = rowptr[i];
      } else {
        rowptr[i] = current;
      }
    }
  }
};

void solve(int t) {
  int r, c;
  std::cin >> r >> c;
  Mat mat{r, c};
  char line[c + 1];
  for(int i = 0; i < r; ++i) {
    std::cin >> line;
    mat.putline(i, line);
  }
  mat.whatever();
  std::cout << "Case #" << t << ":\n";
  std::cout << mat.data;
}

void unit_tests() {
}

int main() {
  UNIT_TESTS();
  int T;
  std::cin >> T;
  for(int t = 1; t <= T; ++t) {
    solve(t);
  }
  return 0;
}
