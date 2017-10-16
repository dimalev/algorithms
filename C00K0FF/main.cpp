#include <iostream>
#include <algorithm>
#include <vector>

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

int main() {
#ifdef UNITS
  unit_tests();
  return 0;
#endif
  int T;
  std::cin >> T;
  std::vector<std::string> dict{
    "cakewalk", "simple", "easy","easy-medium","medium", "medium-hard","hard"};
  fr(t,0,T) {
    int N;
    std::cin >> N;
    std::vector<bool> checks(7);
    fr(i,0,N) {
      std::string diff;
      std::cin >> diff;
      TRACE_LINE("<< " << diff);
      checks[std::distance(dict.begin(), std::find(dict.begin(), dict.end(), diff))] = true;
    }
    if(checks[0] && checks[1] && checks[2] && (checks[3] || checks[4]) && (checks[5] || checks[6]))
      std::cout << "Yes\n";
    else std::cout << "No\n";
  }
  return 0;
}
