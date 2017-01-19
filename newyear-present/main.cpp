#include <stdint.h>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else

#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)
#define UNIT_TESTS()

#endif

int64_t N;
std::map<int64_t, int64_t> L;

int64_t C(const int64_t &n, const int64_t &k) {
  int64_t res = 1;
  for(int64_t i = n - k + 1; i <= n; ++i) res *= i;
  for(int64_t i = 2; i <= k; ++i) res /= i;
  return res;
}

int64_t count_two(const int64_t &l) {
  //std::cout << "-- " << l << " for two:\n";

  std::vector<std::pair<std::map<const int64_t, int64_t>::iterator, std::map<const int64_t, int64_t>::iterator>> L2;
  std::map<int64_t, int64_t>::iterator lines = L.begin();
  long long all_combs = 0;
  while(lines != L.end()) {
    if(2 * lines->first >= l) break;
    std::map<int64_t, int64_t>::iterator lines2 = L.find(l - lines->first);
    if(lines2 != L.end())  {
      L2.push_back(std::pair<std::map<int64_t, int64_t>::iterator, std::map<int64_t, int64_t>::iterator>(lines, lines2));
      all_combs += lines->second * lines2->second;
    }
    ++lines;
  }

  int64_t res = 0;
  if(l % 2 == 0) {
    int64_t l2 = l / 2;
    auto l2it = L.find(l2);
    if(l2it != L.end()) {
      // all four segments are equal
      if(l2it->second >= 4) {
        int64_t comb = C(l2it->second, 4);
        //std::cout << comb << " for all 4 segments equal (" << l2it->second << ")\n";
        res += comb;
      } //else std::cout << "cannot have all 4 segments equal\n";
      // two are equal, two more - are different
      if(l2it->second >= 2) {
        res += all_combs * C(l2it->second, 2);
      } //else std::cout << "cannot have one line of 2 equal segments\n";
    }
  } //else std::cout << "cannot have 2 equal\n";
  // we iterate over shorter stick
  auto lines_pair_it = L2.begin();
  while(lines_pair_it != L2.end()) {
    lines = lines_pair_it->first;
    // two sticks are equal - third is equal too
    auto lines2 = lines_pair_it->second;
    if(lines->second >= 2 && lines2->second >= 2) {
      int64_t comb = C(lines->second, 2) * C(lines2->second, 2);
      //std::cout << "for 2x" << lines->first << " and 2x" << lines2->first << " " << comb << " combinations\n";
      res += comb;
    }
    auto lines_pair_it2 = lines_pair_it;
    ++lines_pair_it2;
    while(lines_pair_it2 != L2.end()) {
      auto lines3 = lines_pair_it2->first;
      auto lines32 = lines_pair_it2->second;
      int64_t comb = lines->second * lines2->second * lines3->second * lines32->second;
      //std::cout << "for " << lines->first << " + " << lines2->first << " and " << lines3->first << " + " << lines32->first << " threre are " << comb << " combinations\n";
      res += comb;
      ++lines_pair_it2;
    }
    ++lines_pair_it;
  }
  return res;
}

std::map<int64_t, std::map<int64_t, int64_t>*> two_other;

int64_t find_two_other(const int64_t &l2, const int64_t &lf) {
  int64_t res = 0;
  auto lines2 = L.upper_bound(l2 - lf);
  while(lines2 != L.end()) {
    if(2 * lines2->first >= l2) break;
    auto third = L.find(l2 - lines2->first);
    if(third != L.end()) {
      int64_t comb = third->second * lines2->second;
      //std::cout << comb << " for " << lines.first << " " << lines2->first << " " << third->first << "\n";
      res += comb;
    } //else std::cout << "no third for " << lines.first << " " << lines2->first << "\n";
    ++lines2;
  }
  return res;
}

int64_t count_three(const int64_t &l) {
  //std::cout << "-- " << l << " for three:\n";
  int64_t res = 0;
  // all three equal
  if(l % 3 == 0) {
    auto l3it = L.find(l / 3);
    if(l3it != L.end() && l3it->second >= 3) {
      int64_t comb = C(l3it->second, 3);
      //std::cout << comb << " of 3 equal\n";
      res += comb;
    } //else std::cout << "No 3 equal\n";
  }
  for(auto lines : L) {
    if(lines.first >= l) break;
    // two equal
    if(2 * lines.first < l && 3 * lines.first != l && lines.second >= 2) {
      auto third = L.find(l - 2 * lines.first);
      if(third != L.end()) {
        int64_t comb = third->second * C(lines.second, 2);
        //std::cout << comb << " for 2 equal: 2x" << lines.first << " and " << third->first << "\n";
        res += comb;
      } //else std::cout << "no third for two equal " << lines.first << "\n";
    } //else std::cout << "no 2 equal for " << lines.first << "\n";
    // three different
    int64_t l2 = l - lines.first;
    // we asume lines - is largest, lines2 - smallest, and third is in between
    res += find_two_other(l2, lines.first) * lines.second;
  }
  return res;
}

void unit_tests() {
}

int main() {
  UNIT_TESTS()
  std::cin >> N;
  for(int64_t i = 0; i < N; ++i) {
    int64_t l;
    std::cin >> l;
    auto line = L.find(l);
    if(line == L.end()) {
      L.emplace(l, 1);
    } else ++line->second;
  }
  int64_t res = 0;
  for(auto lines : L) {
    if(lines.second == 2) {
      res += count_two(lines.first);
    } else if(lines.second >= 3) {
      int64_t comb = C(lines.second, 2) * count_two(lines.first);
      //std::cout << "for " << lines.first << " (" << lines.second << ") with 2x2 got " << comb << " combinations\n";
      res += comb;
      comb = C(lines.second, 3) * count_three(lines.first);
      //std::cout << "for " << lines.first << " (" << lines.second << ") with 1x3 got " << comb << " combinations\n";
      res += comb;
    }
  }
  std::cout << res;
  return 0;
}
