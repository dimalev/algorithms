/*
  abc
  cbv

  a b c c b v
v x x 0 < < <
b x x 0
c 0 0 0
c ^
b ^
a ^
 */

#include <iostream>
#include <string>
#include <cstring>

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else

#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)

#endif

void solve() {
  std::string one, two, summ;
  std::cin >> one >> two;
  summ = one + two;
  int one_s = one.size();
  int two_s = two.size();
  int summ_s = summ.size();
  int *matrix = new int[summ_s * summ_s];
  char *last = new char[summ_s * summ_s];
  for(int i = 0; i < one_s; ++i) {
    for(int j = 0; j < two_s; ++j) {
      if(summ[i] == summ[summ_s - j - 1]) {
        last[i * summ_s + j] = summ[i];
        if(i == 0 || j == 0) matrix[i * summ_s + j] = 1;
        else matrix[i * summ_s + j] = matrix[(i - 1) * summ_s + j - 1] + 1;
      } else {
        if(i > 0 && j > 0) {
          if(matrix[(i - 1) * summ_s + j] == matrix[i * summ_s + j - 1]) {
            last[i * summ_s + j] = std::min(last[(i - 1) * summ_s + j], last[i * summ_s + j - 1]);
            matrix[i * summ_s + j] = matrix[(i - 1) * summ_s + j];
          } else if(matrix[(i - 1) * summ_s + j] > matrix[i * summ_s + j - 1]) {
            last[i * summ_s + j] = last[(i - 1) * summ_s + j];
            matrix[i * summ_s + j] = matrix[(i - 1) * summ_s + j];
          } else {
            last[i * summ_s + j] = last[i * summ_s + j - 1];
            matrix[i * summ_s + j] = matrix[i * summ_s + j - 1];
          }
        } else if(i == 0) {
          matrix[i * summ_s + j] = matrix[i * summ_s + j - 1];
          last[i * summ_s + j] = last[i * summ_s + j - 1];
        } else {
          matrix[i * summ_s + j] = matrix[(i - 1) * summ_s + j];
          last[i * summ_s + j] = last[(i - 1) * summ_s + j];
        }
      }
    }
  }
  if(matrix[(one_s - 1) * summ_s + two_s - 1] == 0) {
    std::cout << -1 << std::endl;
    return;
  }
  bool *valid = new bool[summ_s * summ_s];
  std::memset(valid, false, sizeof(bool) * summ_s * summ_s);
  for(int i = 0; i < one_s; ++i)
    valid[i * summ_s + two_s - 1] = matrix[i * summ_s + two_s - 1] > 0;
  for(int i = 0; i < two_s; ++i)
    valid[(one_s - 1) * summ_s + i] = matrix[(one_s - 1) * summ_s + i] > 0;

  for(int i = 0; i < summ_s; ++i) {
    int start = i >= one_s ? 0 : two_s;
    for(int j = start; j < summ_s; ++j) {
      if(summ[i] == summ[summ_s - j - 1] && i > 0 && j > 0 && valid[(i - 1) * summ_s + j - 1]) {
        valid[i * summ_s + j] = true;
        matrix[i * summ_s + j] = matrix[(i - 1) * summ_s + j - 1] + 1;
        last[i * summ_s + j] = summ[i];
      } else {
        bool up_valid = (i > 0 && valid[(i - 1) * summ_s + j]);
        bool left_valid = (j > 0 && valid[i * summ_s + j - 1]);
        if(!up_valid && !left_valid) continue;
        valid[i * summ_s + j] = true;
        if(up_valid && left_valid) {
          if(matrix[(i - 1) * summ_s + j] == matrix[i * summ_s + j - 1]) {
            matrix[i * summ_s + j] = matrix[(i - 1) * summ_s + j];
            last[i * summ_s + j] = std::min(last[(i - 1) * summ_s + j], last[i * summ_s + j - 1]);
          } else if(matrix[(i - 1) * summ_s + j] > matrix[i * summ_s + j - 1]) {
            matrix[i * summ_s + j] = matrix[(i - 1) * summ_s + j];
            last[i * summ_s + j] = last[(i - 1) * summ_s + j];
          } else {
            matrix[i * summ_s + j] = matrix[i * summ_s + j - 1];
            last[i * summ_s + j] = last[i * summ_s + j - 1];
          }
        } else if(left_valid) {
          matrix[i * summ_s + j] = matrix[i * summ_s + j - 1];
          last[i * summ_s + j] = last[i * summ_s + j - 1];
        } else {
          matrix[i * summ_s + j] = matrix[(i - 1) * summ_s + j];
          last[i * summ_s + j] = last[(i - 1) * summ_s + j];
        }
      }
    }

#ifdef ALGO_DEBUG
  for(int i = 0; i < summ_s; ++i) {
    if(i == two_s) std::cerr << "\t";
    std::cerr << "\t" << summ[summ_s - i - 1];
  }
  std::cerr << std::endl;
  for(int i = 0; i < summ_s; ++i) {
    if(i == one_s) std::cerr << std::endl;
    std::cerr << summ[i];
    for(int j = 0; j < summ_s; ++j) {
      if(j == two_s) std::cerr << "\t";
      if(i < one_s - 1 && j < two_s - 1)
        std::cerr << "\t" << matrix[i * summ_s + j] << ".";
      else if(valid[i * summ_s + j])
        std::cerr << "\t" << matrix[i * summ_s + j] << last[i * summ_s + j];
      else std::cerr << "\tx";
    }
    std::cerr << std::endl;
  }
    std::cerr << std::endl;
#endif
  }

  int x = summ_s - 1, y = summ_s - 1;
  while(x >= 0 && y >= 0) {
    if(summ[x] == summ[summ_s - (y + 1)] &&
       (x == 0 || y == 0 || matrix[(x - 1) * summ_s + y - 1] + 1 == matrix[x * summ_s + y])) {
      std::cout << summ[x];
      --x; --y;
    } else {
      bool left_valid =
        matrix[x * summ_s + y] == matrix[x * summ_s + y - 1] &&
        ((x < one_s - 1 && y < two_s - 1) || valid[x * summ_s + y - 1]) &&
        last[x * summ_s + y] == last[x * summ_s + y - 1];
      // bool up_valid =
      //   matrix[x * summ_s + y] == matrix[(x - 1) * summ_s + y] &&
      //   valid[(x - 1) * summ_s + y] && last[x * summ_s + y] == last[(x - 1) * summ_s + y];
      if(!left_valid) --x;
      else --y;
    }
  }
  std::cout << std::endl;
}

int main() {
  int T;
  std::cin >> T;
  while(T--) solve();
  return 0;
}
