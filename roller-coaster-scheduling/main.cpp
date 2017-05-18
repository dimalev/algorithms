#include <iostream>
#include <algorithm>
#include <set>

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

void solve(int t) {
  int N, C, M;
  std::cin >> N >> C >> M;
  int tickets[C][N];
  std::set<int, int> places[C];
  for(int i = 0; i < C; ++i)
    for(int j = 0; j < N; ++j) tickets[i][j] = 0;
  for(int i = 0; i < M; ++i) {
    int p, c;
    std::cin >> p >> c;
    tickets[c - 1][p - 1]++;
    places[c - 1].insert(p - 1);
  }
  int rides = 0, promotions = 0;
  for(int c = 0; c < C; ++c) {
    for(int place : places[c]) {
      int ticket_count = tickets[c][place];
      std::set<int> busy;
      busy.insert(place);
    }
  }
  std::cout << "Case #" << t << ": " << rides << " " << promotions << "\n";
}

int main() {
  UNIT_TESTS();
  int T;
  std::cin >> T;
  for(int t = 1; t <= T; ++t) solve(t);
  return 0;
}
