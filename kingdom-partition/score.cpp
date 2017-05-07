#include <iostream>
#include <string>
#include <map>
#include <cmath>

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
  int cols, rows = 0;
  char vals[50][50];
  std::string line;
  while(std::cin >> line) {
    if(line.size() == 0) break;
    cols = line.size();
    for(int c = 0; c < cols; ++c) {
      vals[rows][c] = line[c];
    }
    ++rows;
  }
  std::map<char, int> S, P;
  for(int r = 0; r < rows; ++r) {
    for(int c = 0; c < cols; ++c) {
      ++S[vals[r][c]];
      if(r == 0 || vals[r - 1][c] != vals[r][c]) ++P[vals[r][c]];
      if(r == rows - 1 || vals[r + 1][c] != vals[r][c]) ++P[vals[r][c]];
      if(c == 0 || vals[r][c - 1] != vals[r][c]) ++P[vals[r][c]];
      if(c == cols - 1 || vals[r][c + 1] != vals[r][c])  ++P[vals[r][c]];
    }
  }
  int count = 0;
  double total = 0;
  for(auto squares : S) {
    char owner = squares.first;
    int area = squares.second;
    int perimeter = P[owner];
    total += double(area) / (double(perimeter) * double(perimeter));
    std::cout << owner << ": S=" << area << " P=" << perimeter << std::endl;
    ++count;
  }
  std::cout << std::round(total / count * 160000) << std::endl;
  return 0;
}
