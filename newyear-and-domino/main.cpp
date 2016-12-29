#include <iostream>
#include <string>

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else

#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)
#define UNIT_TESTS()

#endif

constexpr int MAX_N = 500;

void unit_tests() {
}

int main() {
  UNIT_TESTS();
  int board[MAX_N][MAX_N], hor[MAX_N][MAX_N], ver[MAX_N][MAX_N];
  int w, h;
  std::cin >> h >> w;
  for(int i = 0; i < h; ++i) {
    std::string line;
    std::cin >> line;
    for(int j = 0; j < w; ++j) {
      board[i][j] = (line.at(j) == '#' ? 1 : 0);
    }
  }
  for(int i = 0; i < h; ++i) {
    for(int j = 0; j < w; ++j) {
      ver[i][j] = 0;
      if(i > 0) ver[i][j] += ver[i - 1][j];
      if(j > 0) ver[i][j] += ver[i][j - 1];
      if(i > 0 && j > 0) ver[i][j] -= ver[i - 1][j - 1];
      if(i > 0 && board[i][j] == 0 && board[i - 1][j] == 0) ++ver[i][j];

      hor[i][j] = 0;
      if(i > 0) hor[i][j] += hor[i - 1][j];
      if(j > 0) hor[i][j] += hor[i][j - 1];
      if(i > 0 && j > 0) hor[i][j] -= hor[i - 1][j - 1];
      if(j > 0 && board[i][j] == 0 && board[i][j - 1] == 0) ++hor[i][j];
    }
  }
#ifdef ALGO_DEBUG
  for(int i = 0; i < h; ++i) {
    for(int j = 0; j < w; ++j)
      std::cerr << ver[i][j] << "\t";
    std::cerr << std::endl;
  }
  std::cerr << std::endl;
  for(int i = 0; i < h; ++i) {
    for(int j = 0; j < w; ++j)
      std::cerr << hor[i][j] << "\t";
    std::cerr << std::endl;
  }
  std::cerr << std::endl;
#endif
  int q;
  std::cin >> q;
  for(int i = 0; i < q; ++i) {
  int r1, c1, r2, c2;
  std::cin >> r1 >> c1 >> r2 >> c2;
    --r1; --r2; --c1; --c2;
    int res = hor[r2][c2] - hor[r2][c1] + ver[r2][c2] - ver[r1][c2];
    if(r1 > 0) res = res - hor[r1 - 1][c2] + hor[r1 - 1][c1];
    if(c1 > 0) res = res - ver[r2][c1 - 1] + ver[r1][c1 - 1];
    std::cout << res << std::endl;
  }
  return 0;
}
