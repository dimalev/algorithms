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

#include <iterator>
#include <iostream>
#include <array>
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
char line[MAX_N];
std::array<std::array<int, MAX_N>, MAX_N> matrix;
std::array<std::array<int, MAX_N>, MAX_N> partial_matrix;

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

int partial_longest_palyndrome(int start, int end) {
  if(start >= end) return 0;
  for(int i = N - end; i < N - start; ++i) {
    for(int j = start; j < end; ++j) {
      if(line[N - i - 1] == line[j]) {
        if(i > start && j > start) partial_matrix[i][j] = partial_matrix[i - 1][j - 1] + 1;
        else partial_matrix[i][j] = 1;
      } else {
        if(i == start) {
          if(j == start) partial_matrix[i][j] = 0;
          else partial_matrix[i][j] = partial_matrix[i][j - 1];
        } else if(j == start) {
          partial_matrix[i][j] = partial_matrix[i - 1][j];
        } else partial_matrix[i][j] = std::max(partial_matrix[i - 1][j], partial_matrix[i][j - 1]);
      }
    }
  }
  return partial_matrix[end - 1][end - 1];
}

int main() {
  int T;
  std::cin >> T;
  for (int t = 0; t < T; ++t) {
    int K;
    std::cin >> N >> K;
    std::cin >> line;
    std::cout << "size: " << N
              << " delta: " << K
              << " line: " << line << std::endl;
    if(K == 0) std::cout << (26 * (N + 1)) << std::endl;
    else if(K > 2) {
      std::cout << 0 << std::endl;
    } else {
      int L = longest_palyndrome();
      for(int i = 0; i < N; ++i) {
        std::copy(matrix[i].begin(), std::next(matrix[i].begin(), N), std::ostream_iterator<int>(std::cerr, "\t"));
        std::cerr << std::endl;
      }
      TRACE_LINE("longest line " << L);
      int res = 0;
      for(int i = 0; i <= N; ++i) { // put char in front of i-th char ..
        bool is_any_letter_good = false;
        if(i > 0 && i < N) {
          int newL = 2 * matrix[N - i - 1][i - 1] + 1;
          // TRACE_LINE("Trying to put char on " << i << "-th position length = " << newL);
          if(newL >= L + K) { // .. to mirror itselft
            res += 26;
            is_any_letter_good = true;
            TRACE_LINE("Put any char before " << i << "-th");
          }
        }
        if(!is_any_letter_good) {
          std::array<bool, 26> letters;
          std::fill(letters.begin(), letters.end(), false);
          int increment = 0;
          for(int j = 0; j < i; ++j) { // .. to mirror j-th char
            int L1 = (j >= 1 && N - i - 1 >= 0) ? matrix[N - i - 1][j - 1] : 0;
            int L2 = partial_longest_palyndrome(j + 1, i);
            int newL = 2 * L1 + L2 + 2;
            if(newL >= L + K) {
              if(!letters[line[j] - 'a']) {
                // TRACE_LINE("put char before " << i << " to mirror " << j << "-th char new length = " << newL << " (1)");
                // TRACE_LINE(" -- wings: " << L1 << " up to center: " << L2);
                letters[line[j] - 'a'] = true;
                ++increment;
              }
            };
          }
          for(int j = i; j < N; ++j) { // .. to mirror j-th char
            int L1 = (i > 0 && N - j >= 0) ? matrix[N - j][i - 1] : 0;
            int L2 = partial_longest_palyndrome(i, j);
            int newL = 2 * L1 + L2 + 2;
            TRACE_LINE("put char before " << i << " to mirror " << j << "-th char new length = " << newL << " (2)");
            TRACE_LINE(" -- wings: " << L1 << " up to center: " << L2);
            if(newL >= L + K) {
              if(!letters[line[j] - 'a']) {
                letters[line[j] - 'a'] = true;
                ++increment;
              }
            };
          }
          if(increment > 0) {
            TRACE("Put " << increment << " chars before " << i << "-th");
            for(int i = 0; i < 26; ++i) if(letters[i]) std::cerr << " " << (char)('a' + i);
            std::cerr << std::endl;
          }
          res += increment;
        }
      }
      std::cout << res << std::endl;
    }
  }
  return 0;
}
