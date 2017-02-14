#include <iostream>

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
  int a, b;
  std::cin >> a >> b;
  std::cout << a * b << std::endl;
}
#endif

int main() {
#ifdef UNITS
  unit_tests();
  return 0;
#endif
  int a, b, sum;
  TRACE_LINE("Start");
  std::cin >> a >> b;
  TRACE("a = " << a);
  TRACE_LINE(" b = " << b);
  ASSERT(a == b);
  sum = a + b;
  TRACE_LINE("Result = " << sum);
  std::cout << sum;
  TRACE_LINE("We are done");
  return 0;
}
