#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>

#define fr(v,s,e) for(int v = s; v < e; ++v)
#define fl(v,s,e) for(int v = s; v > e; --v)

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

int opposits[] = {3, 4, 5, 0, 1, 2};

class cube {
public:
  explicit cube(std::vector<int> faces) {
    values.resize(6); ids.resize(6);
    values[0] = 0;
    ids[0] = 0;
    fr(i,0,5) {
      values[i+1] = faces[i];
      ids[faces[i]] = i + 1;
    }
  }

  bool test(std::set<int> neer[6]) {
    for(int i = 0; i < 6; ++i) {
      int opposit = values[opposits[ids[i]]];
      if(neer[i].find(opposit) != neer[i].end()) return false;
    }
    return true;
  }

  std::string str() {
    std::stringstream ss;
    fr(i,0,6) {
      if(i > 0) ss << " ";
      ss << values[opposits[ids[i]]]+1;
    }
    return ss.str();
  }

  std::vector<int> values, ids;
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
  int T;
  std::cin >> T;
  fr(t,0,T) {
    int N;
    std::cin >> N;
    std::set<int> neers[6];
    int prev;
    std::cin >> prev;
    --prev;
    bool boolshit = false;
    fr(i,1,N) {
      int next;
      std::cin >> next;
      --next;
      neers[prev].insert(next);
      neers[next].insert(prev);
      if(prev == next) boolshit = true;
      prev = next;
    }
    if(boolshit) {
      std::cout << "-1\n";
      continue;
    }
    std::vector<int> faces{1,2,3,4,5};
    bool found = false;
    while(!found && std::next_permutation(faces.begin(), faces.end())) {
      cube another(faces);
      if(another.test(neers)) {
        std::cout << another.str() << "\n";
        found = true;
      }
    }
    if(!found) std::cout << "-1\n";
  }
  return 0;
}
