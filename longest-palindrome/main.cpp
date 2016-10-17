#include <iostream>
#include <algorithm>

const int MAX_N = 3000;

int find_common(char * const line, int L, int left_start, int right_start) {
  if (left_start < 0) return 0;
  if (right_start >= L) return 0;
  int max_left = left_start + 1;
  int max_right = L - right_start;
  int total_max = std::min(max_left, max_right);
  for (int i = 0; i < total_max; ++i) {
    if (line[left_start - i] != line[right_start + i]) return i;
  }
  return total_max;
}

void find_odd(char* const line, int L, int pivot, int &max, int &left_boosted, int &right_boosted) {
  int max_part = find_common(line, L, pivot, pivot);
  max = 2 * (max_part - 1) + 1;
  int max_left = pivot + 1;
  int max_right = L - pivot;
  if (max_part == max_left && max_part == max_right) {
    left_boosted = -1;
    right_boosted = max; // if we exosted all the line
  }
  else if (max_part < max_left && max_part < max_right) { // if there are parts from both sides
    int max_left_part = find_common(line, L, pivot - max_part - 1, pivot + max_part) + 1;
    int max_right_part = find_common(line, L, pivot - max_part, pivot + max_part + 1) + 1;
    left_boosted = (max_part + max_left_part - 1) * 2 + 1;
    right_boosted = (max_part + max_right_part - 1) * 2 + 1;
  }
  else {
    left_boosted = -1;
    right_boosted = max + 2; // there is a part from only one side
  }
}

/*
   p
012|3456789
asd|dsz

pivot = 3
max_part = 2
max_left = 3
max_right = 6 - 3 = 3


*/

void find_even(char * const line, int L, int pivot, int &max, int &left_boosted, int &right_boosted) {
  int max_part = find_common(line, L, pivot - 1, pivot);
  int max_left = pivot;
  int max_right = L - pivot;
  max = max_part * 2;
  if (max_part == max_right && max_part == max_left) {
    left_boosted = -1;
    right_boosted = max;
  }
  else if (max_part < max_right && max_part < max_left) {
    int max_left_part = find_common(line, L, pivot - max_part - 2, pivot + max_part) + 1;
    int max_right_part = find_common(line, L, pivot - max_part - 1, pivot + max_part + 1) + 1;
    left_boosted = (max_part + max_left_part) * 2;
    right_boosted = (max_part + max_right_part) * 2;
  }
  else {
    left_boosted = -1;
    right_boosted = max + 2;
  }
}

int main() {
  int T;
  std::cin >> T;
  for (int t = 0; t < T; ++t) {
    int N, K;
    std::cin >> N >> K;
    char line[MAX_N + 1];
    std::cin >> line;
    if (K == 0) std::cout << (26 * (N + 1)) << std::endl;
    else {
      int max[MAX_N + 2];
      std::fill(max, max + N + 1, 0);
      int max_polyndrome = 0;
      for (int i = 0; i < N; ++i) {
        int max_current, max_left_boosted, max_right_boosted;
        find_odd(line, N, i, max_current, max_left_boosted, max_right_boosted);
        //std::cout << "for pivot " << i << " max = " << max_current << ", left = " << max_left_boosted << ", right = " << max_right_boosted << std::endl;
        max_polyndrome = std::max(max_current, max_polyndrome);
        if (max_left_boosted >= 0) ++max[max_left_boosted];
        ++max[max_right_boosted];
      }
      //std::cout << "---" << std::endl;
      for (int i = 0; i <= N; ++i) {
        int max_current, max_left_boosted, max_right_boosted;
        find_even(line, N, i, max_current, max_left_boosted, max_right_boosted);
        //std::cout << "for pivot " << i << " max = " << max_current << ", left = " << max_left_boosted << ", right = " << max_right_boosted << std::endl;
        max_polyndrome = std::max(max_current, max_polyndrome);
        if (max_left_boosted >= 0) ++max[max_left_boosted];
        ++max[max_right_boosted];
      }
      int total = 0;
      for (int i = max_polyndrome + K; i <= N + 1; ++i) total += max[i];
      std::cout << total << std::endl;
    }
  }
  return 0;
}
