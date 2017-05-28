 #include <iostream>
#include <queue>
#include <algorithm>

#ifdef UNITS
#include "../test/units.cpp"
#endif

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else
#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)
#endif

#ifdef UNITS
void unit_tests() {
  test_header("test units");
}
#endif

void solve() {
  int N, M;
  std::cin >> N;
  int snake[100], ladder[100];
  std::fill_n(snake, 100, -1);
  std::fill_n(ladder, 100, -1);
  for(int i = 0; i < N; ++i) {
    int start, end;
    std::cin >> start >> end;
    --start; --end;
    ladder[std::min(start, end)] = std::max(start, end);
  }
  std::cin >> M;
  for(int i = 0; i < M; ++i) {
    int start, end;
    std::cin >> start >> end;
    --start; --end;
    snake[std::max(start, end)] = std::min(start, end);
  }
  int way[100];
  std::fill_n(way, 100, 10000);
  std::queue<int> cells;
  way[0] = 0;
  cells.push(0);
  while(!cells.empty()) {
    int cell = cells.front();
    cells.pop();
    for(int s = 1; s <= 6; ++s) {
      int next_cell = cell + s;
      if(next_cell > 99) {
        break;
      }
      if(snake[next_cell] != -1) {
        next_cell = snake[next_cell];
      }
      if(ladder[next_cell] != -1) {
        next_cell = ladder[next_cell];
      }
      if(way[next_cell] > way[cell] + 1) {
        way[next_cell] = way[cell] + 1;
        cells.push(next_cell);
      }
    }
  }
  // for(int i = 0; i < 100; ++i) {
  //   std::cout << way[i] << " ";
  // }
  // std::cout << std::endl;
  std::cout << (way[99] == 10000 ? -1 : way[99]) << std::endl;
}

int main() {
#ifdef UNITS
  unit_tests();
  return 0;
#endif
  int T;
  std::cin >> T;
  for(int t = 0; t < T; ++t) solve();
  return 0;
}
