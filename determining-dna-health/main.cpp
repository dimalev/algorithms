#include <iostream>
#include <set>
#include <algorithm>
#include <limits>
#include <vector>
#include <string>
#include <map>

#define fr(v,s,e) for(long v = s; v < e; ++v)
#define fl(v,s,e) for(long v = s; v > e; --v)

#ifdef UNITS
#include "../test/units.cpp"
#endif

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else
#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)
#endif

long costs[100000];

class link {
  link *children[26];
  std::set<long> ids;
  std::map<long, long> summs;
  bool summCached = false;
  long min, max;
public:
  link() {
    std::fill_n(children, 26, nullptr);
    min = std::numeric_limits<long>::max();
    max = std::numeric_limits<long>::min();
  }

  ~link() {
    fr(i, 0, 26) {
      delete children[i];
    }
  }

  void near(long id) {
    min = std::min(min, id);
    max = std::max(max, id);
  }

  bool hasChild(const char &c, long l, long u) const {
    if(l > max || u < min) return false;
    if(children[c - 'a'] == nullptr) return false;
    if(l > children[c - 'a']->max || u < children[c - 'a']->min) return false;
    return true;
  }

  link* getChild(const char &c) {
    if(children[c - 'a'] == nullptr)
      children[c - 'a'] = new link();
    return children[c - 'a'];
  }

  link& operator<<(const long &id) {
    ids.insert(id);
    return *this;
  }

  bool hasIds(long start, long end) {
    auto small = ids.lower_bound(start);
    auto big = ids.upper_bound(end);
    return small != ids.end() && big != ids.begin();
  }

  long getSum(long lo, long hi) {
    if(!summCached) {
      long summ = 0;
      for(long id : ids) {
        summ += costs[id];
        summs[id] = summ;
      }
      summCached = true;
    }
    auto start = summs.lower_bound(lo);
    auto end = summs.upper_bound(hi);
    if(start == summs.end() || end == summs.begin()) return 0;
    --end;
    if(start == summs.begin()) return end->second;
    --start;
    return end->second - start->second;
  }
};

#ifdef UNITS
void unit_tests() {
  test_header("test units");
}
#endif

int main() {
#ifdef UNITS
  unit_tests();
  return 0;
#endif
  link* root = new link();
  long N;
  std::cin >> N;
  fr(i, 0, N) {
    std::string line;
    std::cin >> line;
    long l = line.length();
    link *curr = root;
    curr->near(i);
    fr(j, 0, l) {
      curr = curr->getChild(line[j]);
      curr->near(i);
    }
    *curr << i;
  }
  fr(i, 0, N) {
    std::cin >> costs[i];
  }
  long M;
  std::cin >> M;
  long min = std::numeric_limits<long>::max();
  long max = std::numeric_limits<long>::min();
  fr(i,0,M) {
    long l, u;
    std::string line;
    std::cin >> l >> u >> line;
    const char *buffer = line.c_str();
    long s = line.length();
    long cost = 0;
    std::vector<link*> curr{};
    int total = 0;
    fr(i, 0, s) {
      int place = 0;
      fr(j, 0, total) {
        link *curr_link = curr[j];
        if(curr_link->hasChild(buffer[i], l, u)) {
          link* next_link = curr_link->getChild(buffer[i]);
          curr[place++] = next_link;
          cost += next_link->getSum(l, u);
        }
      }
      if(root->hasChild(buffer[i], l, u)) {
        link* next_link = root->getChild(buffer[i]);
        if(curr.size() > place) {
          curr[place] = next_link;
        } else curr.push_back(next_link);
        ++place;
        cost += next_link->getSum(l, u);
      }
      curr.resize(place);
      total = place;
    }
    if(cost < min) min = cost;
    if(cost > max) max = cost;
  }
  std::cout << min << " " << max << "\n";
  delete root;
  return 0;
}
