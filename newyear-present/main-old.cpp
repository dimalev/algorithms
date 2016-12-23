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

long long N;
std::map<long long, long long> L;

long long C(long long n, long long k) {
  long long res = 1;
  for(long long i = n - k + 1; i <= n; ++i) res *= i;
  for(long long i = 2; i <= k; ++i) res /= i;
  return res;
}

long long count_two(long long l) {
  //std::cout << "-- " << l << " for two:\n";

  std::vector<std::pair<std::map<const long long, long long>::iterator, std::map<const long long, long long>::iterator>> L2;
  std::map<long long, long long>::iterator lines = L.begin();
  long long all_combs = 0;
  while(lines != L.end()) {
    if(2 * lines->first >= l) break;
    std::map<long long, long long>::iterator lines2 = L.find(l - lines->first);
    if(lines2 != L.end())  {
      L2.push_back(std::pair<std::map<long long, long long>::iterator, std::map<long long, long long>::iterator>(lines, lines2));
      all_combs += lines->second * lines2->second;
    }
    ++lines;
  }
  
  long long res = 0;
  if(l % 2 == 0) {
    long long l2 = l / 2;
    auto l2it = L.find(l2);
    if(l2it != L.end()) {
      // all four segments are equal
      if(l2it->second >= 4) {
        long long comb = C(l2it->second, 4);
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
      long long comb = C(lines->second, 2) * C(lines2->second, 2);
      //std::cout << "for 2x" << lines->first << " and 2x" << lines2->first << " " << comb << " combinations\n";
      res += comb;
    }
    auto lines_pair_it2 = lines_pair_it;
    ++lines_pair_it2;
    while(lines_pair_it2 != L2.end()) {
      auto lines3 = lines_pair_it2->first;
      auto lines32 = lines_pair_it2->second;
      long long comb = lines->second * lines2->second * lines3->second * lines32->second;
      //std::cout << "for " << lines->first << " + " << lines2->first << " and " << lines3->first << " + " << lines32->first << " threre are " << comb << " combinations\n";
      res += comb;
      ++lines_pair_it2;
    }
    ++lines_pair_it;
  }
  return res;
}

std::map<long long, std::map<long long, long long>*> two_other;

long long find_two_other(long long l2, long long lf) {
  auto l2_it = two_other.find(l2);
  if(l2_it != two_other.end()) {
    auto lf_it = l2_it->second->find(lf);
    if(lf_it != l2_it->second->end()) return lf_it->second;
  }
  long long res = 0;
  auto lines2 = L.upper_bound(l2 - lf);
  while(lines2 != L.end()) {
    if(2 * lines2->first >= l2) break;
    auto third = L.find(l2 - lines2->first);
    if(third != L.end()) {
      long long comb = third->second * lines2->second;
      //std::cout << comb << " for " << lines.first << " " << lines2->first << " " << third->first << "\n";
      res += comb;
    } //else std::cout << "no third for " << lines.first << " " << lines2->first << "\n";
    ++lines2;
  }
  if(l2_it != two_other.end()) {
    l2_it->second->emplace(lf, res);
  } else {
    auto l2_p = two_other.emplace(l2, new std::map<long long, long long>());
    l2_p.first->second->emplace(lf, res);
  }
  return res;
}

long long count_three(long long l) {
  //std::cout << "-- " << l << " for three:\n";
  long long res = 0;
  // all three equal
  if(l % 3 == 0) {
    auto l3it = L.find(l / 3);
    if(l3it != L.end() && l3it->second >= 3) {
      long long comb = C(l3it->second, 3);
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
        long long comb = third->second * C(lines.second, 2);
        //std::cout << comb << " for 2 equal: 2x" << lines.first << " and " << third->first << "\n";
        res += comb;
      } //else std::cout << "no third for two equal " << lines.first << "\n";
    } //else std::cout << "no 2 equal for " << lines.first << "\n";
    // three different
    long long l2 = l - lines.first;
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
  for(long long i = 0; i < N; ++i) {
    long long l;
    std::cin >> l;
    auto line = L.find(l);
    if(line == L.end()) {
      L.emplace(l, 1);
    } else ++line->second;
  }
  long long res = 0;
  for(auto lines : L) {
    if(lines.second == 2) {
      res += count_two(lines.first);
    } else if(lines.second >= 3) {
      long long comb = C(lines.second, 2) * count_two(lines.first);
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
