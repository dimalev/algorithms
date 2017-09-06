#include <iostream>

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
  int s, v1, v2, t1, t2;
  std::cin >> s >>  v1 >> v2 >> t1 >> t2;
  int one = 2 * t1 + s * v1;
  int two = 2 * t2 + s * v2;
  if(one == two) std::cout << "Friendship\n";
  else if(one < two)std::cout << "First\n";
  else std::cout << "Second\n";
  return 0;
}
