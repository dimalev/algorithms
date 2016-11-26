#include <iostream>

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else
#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)
#define UNIT_TESTS()
#endif

void unit_tests() {
  int a, b;
  std::cin >> a >> b;
  std::cout << a * b << std::endl;
}

int main() {
  UNIT_TESTS();
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
