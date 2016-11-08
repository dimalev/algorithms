/*

  a a b
a 1 2
a   1 
b     1

 */

#include <iterator>
#include <iostream>
#include <array>
#include <algorithm>
#include <string>

#ifdef ALGO_DEBUG
#include "../../test/debug.cpp"
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
    return wings_m[left * N + right];
  }

  int center(int left, int right) {
    ASSERT(left <= right);
    return center_m[left * N + right];
  }

  int * getWings() const { return wings_m; }
};

int main() {
  int A, B;
  std::cin >> A >> B;
  std::string line;
  std::cin >> line;
  Palindrome linepal{line};
  int * const wings_m = linepal.getWings();
  for(int i = 0; i < linepal.N; ++i) {
    for(int j = 0; j < linepal.N; ++j) {
      if(j <= i) std::cerr << "x\t";
      else std::cerr << wings_m[i * linepal.N + j] << "\t";
    }
    std::cerr << std::endl;
  }
  for(int t = 0; t < A + B; ++t) {
    int left, right;
    std::cin >> left >> right;
    int longest = t < A ? linepal.center(left, right) : linepal.wings(left, right);
    std::cout << longest << std::endl;
  }
  return 0;
}
