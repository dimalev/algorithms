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
  long long x1,x2,x3, y1,y2,y3;
  std::cin >> x1 >> y1
           >> x2 >> y2
           >> x3 >> y3;
  long long d1 = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1),
      d2 = (x2 - x3) * (x2 - x3) + (y2 - y3) * (y2 - y3),
      d3 = (x3 - x1) * (x3 - x1) + (y3 - y1) * (y3 - y1);
  std::cout << (d1 == d2 && ((x2 - x1) * (y3 - y1) != (x3 - x1) * (y2 - y1)) ? "Yes" : "No") << std::endl;
  return 0;
}

// dx1    dx2
// --- == ---
// dy1    dy2

// dx1 * dy2 == dx2 * dy1

