#include <iostream>
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
  std::vector<std::string> X[100];
  int N;
  std::cin >> N;
  fr(i,0,N) {
    int x;
    std::string s;
    std::cin >> x >> s;
    if(i < N / 2) X[x].push_back("-");
    else X[x].push_back(s);
  }
  bool isFirst = true;
  fr(i,0,100) {
    for(auto &s : X[i]) {
      if(!isFirst) std::cout << " ";
      std::cout << s;
      isFirst = false;
    }
  }
  std::cout << std::endl;
  return 0;
}
