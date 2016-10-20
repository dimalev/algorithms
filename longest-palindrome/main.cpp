/*

M(sequence) = (M_count, M_letter) number of same letters in center

+1 letter:
  for even sequences - any letter in center of sequence
  for any sequence - M_count + 1 of M_letter in each center place of sequence
+2 letter:
  for any sequence any not matched (horizontal/vertical move) can be mirrored on the opposit side
+3 letter:
  impossible!
*/

#include <iostream>
#include <algorithm>

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else

#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)

#endif

constexpr int MAX_N = 3000;

int N;
char line[MAX_N + 1];
int matrix[MAX_N][MAX_N];

int longest_palyndrome() {
  for(int i = 0; i < N; ++i) {
    for(int j = 0; j < N; ++j) {
      if(line[N - i - 1] == line[j]) {
        if(i > 0 && j > 0) matrix[i][j] = matrix[i - 1][j - 1] + 1;
        else matrix[i][j] = 1;
      } else {
        if(i == 0) {
          if(j == 0) matrix[i][j] = 0;
          else matrix[i][j] = matrix[i][j - 1];
        } else if(j == 0) {
          matrix[i][j] = matrix[i - 1][j];
        } else matrix[i][j] = std::max(matrix[i - 1][j], matrix[i][j - 1]);
      }
    }
  }
  return matrix[N - 1][N - 1];
}

int main() {
  int T;
  std::cin >> T;
  for (int t = 0; t < T; ++t) {
    int K;
    std::cin >> N >> K;
    std::cin >> line;
    if(K == 0) std::cout << (26 * (N + 1)) << std::endl;
    else if(K > 2) {
      std::cout << 0 << std::endl;
    } else {
      int L = longest_palyndrome();
      TRACE_LINE("longest line " << L);
      int res = 0;
      if(K == 1 && L % 2 == 0) {
        TRACE_LINE("K = 1 && L : 2");
        int L2 = L / 2;
        for(int i = 0; i <= N; ++i) { // put char in front of i-th char ..
          TRACE_LINE("Trying to put char on " << i << "-th position");
          if(i > 0 && matrix[i - 1][N - i - 1] == L2) { // .. to mirror itselft
            res += 26;
          } else {
            for(int j = 0; j < i; ++j) { // .. to mirror j-th char
              int L1 = (j >= 1 && N - i - 1 >= 0) ? matrix[j - 1][N - i - 1] : 0;
              int L2d = N - i - 1 >= 0 ? matrix[j][N - i - 1] : 0;
              int L2 = (i > 0 && N - j - 2 >= 0) ? matrix[i - 1][N - j - 2] : 0;
              if(2 * L1 + L2d - L2 >= L + 2) ++res;
            }
            for(int j = i; j < N; ++j) { // .. to mirror j-th char
              int L1 = (i > 0 && N - j - 2 >= 0) ? matrix[i - 1][N - j - 2] : 0;
              int L2d = N - i - 1 >= 0 ? matrix[i - 1][N - j - 1] : 0;
              int L2 = (i > 0 && N - j - 2 >= 0) ? matrix[j - 1][N - i - 1] : 0;
              if(2 * L1 + L2d - L2 >= L + 2) ++res;
            }
          }
        }
      } else {
        TRACE_LINE("seargin for K == 2");
        for(int i = 0; i <= N; ++i) { // put char in front of i-th char ..
          for(int j = 0; j < i; ++j) { // .. to mirror j-th char
            int L1 = (j >= 1 && N - i - 1 >= 0) ? matrix[j - 1][N - i - 1] : 0;
            int L2d = N - i - 1 >= 0 ? matrix[j][N - i - 1] : 0;
            int L2 = (i > 0 && N - j - 2 >= 0) ? matrix[i - 1][N - j - 2] : 0;
            if(2 * L1 + L2d - L2 >= L + 2) ++res;
          }
          for(int j = i; j < N; ++j) { // .. to mirror j-th char
            int L1 = (i > 0 && N - j - 2 >= 0) ? matrix[i - 1][N - j - 2] : 0;
            int L2d = i > 0 && N - j - 1 >= 0 ? matrix[i - 1][N - j - 1] : 0;
            int L2 = (i > 0 && N - j - 2 >= 0) ? matrix[j - 1][N - i - 1] : 0;
            if(2 * L1 + L2d - L2 >= L + 2) ++res;
          }
        }
      }
      std::cout << res << std::endl;
    }
  }
  return 0;
}
