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

class Palindrome {
  int *center_m, *wings_m;

  void build_center() {
    for(int i = 0; i < N; ++i) { // move through diagonal
      center_m[i * N + i] = 1; // in line[i..i] we have palyndrome of length 1
      for(int j = i - 1; j >= 0; --j) {
        if(line[i] == line[j]) {
          if(i - j == 1) center_m[j * N + i] = 2;
          else center_m[j * N + i] = center_m[(j + 1) * N + i - 1] + 2;
        } else {
          center_m[j * N + i] = std::max(center_m[(j + 1) * N + i], center_m[j * N + i - 1]);
        }
      }
    }
  }

  void build_wings() {
    for(int i = 0; i < N; ++i) { // left bound
      for(int j = N - 1; j > i; --j) { // right bound
        if(line[i] == line[j]) {
          if(i == 0 || j == N - 1) {
            wings_m[i * N + j] = 2;
          } else {
            wings_m[i * N + j] = wings_m[(i - 1) * N + j + 1] + 2;
          }
        } else {
          if(i == 0) {
            if(j == N - 1) wings_m[i * N + j] = 0;
            else wings_m[i * N + j] = wings_m[i * N + j + 1];
          } else if(j == N - 1) {
            wings_m[i * N + j] = wings_m[(i - 1) * N + j];
          } else wings_m[i * N + j] = std::max(wings_m[(i - 1) * N + j], wings_m[i * N + j + 1]);
        }
      }
    }
  }
public:
  const int N;
  const std::string line;

  Palindrome(std::string inLine) :
    N(inLine.size()),
    line(inLine)
  {
    ASSERT(N < MAX_N);
    center_m = new int[N * N];
    build_center();
    wings_m = new int[N * N];
    build_wings();
  }

  int wings(int left, int right) {
    ASSERT(left < right);
    if(left < 0 || right >= N) return 0;
    return wings_m[left * N + right];
  }

  int center(int left, int right) {
    if(left > right) return 0;
    return center_m[left * N + right];
  }

  int * getWings() const { return wings_m; }
};

int main() {
  int T;
  std::cin >> T;
  for (int t = 0; t < T; ++t) {
    int N, K;
    std::string line;
    std::cin >> N >> K;
    std::cin >> line;
    TRACE_LINE("size: " << N
            << " delta: " << K
            << " line: " << line);
    if(K == 0) std::cout << (26 * (N + 1)) << std::endl;
    else if(K > 2) {
      std::cout << 0 << std::endl;
    } else {
      Palindrome paliline{line};
      int L = paliline.center(0, paliline.N - 1);
      TRACE_LINE("longest line " << L);
      int res = 0;
      for(int i = 0; i <= N; ++i) { // put char in front of i-th char ..
        bool is_any_letter_good = false;
        if(i > 0 && i < N) {
          int newL = paliline.wings(i - 1, i) + 1;
          TRACE_LINE("Trying to put char on " << i << "-th position length = " << newL);
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
          for(int j = 0; j < i && j < N; ++j) { // .. to mirror j-th char
            int L1 = paliline.wings(j - 1, i);
            // (j >= 1 && N - i - 1 >= 0) ? matrix[(N - i - 1) * N + j - 1] : 0;
            int L2 = paliline.center(j + 1, i - 1);
            int newL = L1 + L2 + 2;
            // TRACE_LINE("put char before " << i << " to mirror " << j << "-th char new length = " << newL << " (1)");
            // TRACE_LINE(" -- wings: " << L1 << " up to center: " << L2);
            if(newL >= L + K) {
              if(!letters[line[j] - 'a']) {
                letters[line[j] - 'a'] = true;
                ++increment;
              }
            };
          }
          for(int j = i; j < N; ++j) { // .. to mirror j-th char
            int L1 = paliline.wings(i - 1, j + 1);
            //(i > 0 && N - j > 0) ? matrix[(N - j - 1) * N + i - 1] : 0;
            int L2 = paliline.center(i, j - 1);
            int newL = L1 + L2 + 2;
            // TRACE_LINE("put char before " << i << " to mirror " << j << "-th char new length = " << newL << " (2)");
            // TRACE_LINE(" -- wings: " << L1 << " up to center: " << L2);
            if(newL >= L + K) {
              if(!letters[line[j] - 'a']) {
                letters[line[j] - 'a'] = true;
                ++increment;
              }
            };
          }
#ifdef ALGO_DEBUG
          if(increment > 0) {
            TRACE("Put " << increment << " chars before " << i << "-th");
            for(int i = 0; i < 26; ++i) if(letters[i]) std::cerr << " " << (char)('a' + i);
            std::cerr << std::endl;
          }
#endif
          res += increment;
        }
      }
      std::cout << res << std::endl;
    }
  }
  return 0;
}
