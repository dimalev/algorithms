#include <iostream>
#include <set>
#include <map>
#include <algorithm>

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

#ifdef UNITS
void unit_tests() {
  test_header("test units");
}
#endif

constexpr int BUFFER_SIZE = 6000;

int main() {
#ifdef UNITS
  unit_tests();
  return 0;
#endif
  char buffer[BUFFER_SIZE], print[BUFFER_SIZE];
  std::pair<int, int> current{0, 0};
  std::map<std::pair<int, int>, std::set<int>> steps;
  steps[current].insert(0);
  std::cin >> buffer;
  int step = 0;
  for(int i = 0; buffer[i]; ++i) {
    switch(buffer[i]) {
      case '^': current.first--; break;
      case 'v': current.first++; break;
      case '<': current.second--; break;
      case '>': current.second++; break;
    }
    ++step;
    if(steps.find(current) != steps.end()) {
      for(int start : steps[current]) {
        int l = step - start;
        std::copy_n(buffer + start, l, print);
        print[l] = '\0';
        std::cout << print << "\n";
      }
    }
    steps[current].insert(step);
  }
  return 0;
}
