#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int A[300][300];
long long B[300][300];

inline int sqr(int v) { return v * v; }

int main() {
  int n, m, r;
  cin >> n >> m >> r;
  for(int i = 0; i < n; ++i)
    for(int j = 0; j < m; ++j) cin >> A[i][j];
  long long zor = 0;
  for(int line = -r; line <= r; ++line) {
    int dr = sqrt(r * r - line * line);
    for(int x = max(-line, 0); x <= min(n - 1, n - line - 1); ++x) {
      long long line_sum = 0;
      for(int line_reader = 0; line_reader <= dr; ++line_reader)
        line_sum += A[x + line][line_reader];
      for(int y = 0; y < m; ++y) {
        B[x][y] += line_sum;
        if(y - dr >= 0) line_sum -= A[x + line][y - dr];
        if(y + 1 + dr < m) line_sum += A[x + line][y + 1 + dr];
      }
    }
  }
  for(int i = 0; i < n; ++i)
    for(int j = 0; j < m; ++j) zor ^= B[i][j];
  cout << zor << std::endl;
  return 0;
}
