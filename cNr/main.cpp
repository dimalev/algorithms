#include <iostream>
#include <array>

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else

#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)

#endif

constexpr int M = 1e9;
constexpr int MAX_N = 1000;

std::array<std::array<int, MAX_N + 1>, MAX_N> triangle;
int triangle_height = 0;

void solve() {
  int N;
  std::cin >> N;
  for(int i = triangle_height + 1; i <= N; ++i) {
    triangle[i][0] = triangle[i][i] = 1;
    for(int j = 1; j < i; ++j) {
      triangle[i][j] = (triangle[i - 1][j - 1] + triangle[i - 1][j]) % M;
    }
  }
  std::cout << triangle[N][0];
  for(int k = 1; k <= N; ++k) {
    std::cout << " " << triangle[N][k];
  }
  std::cout << std::endl;
}

int main() {
  int T;
  std::cin >> T;
  triangle[0][0] = 1;
  while(T--) solve();
  return 0;
}
