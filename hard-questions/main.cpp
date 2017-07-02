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
}
#endif

int main() {
#ifdef UNITS
  unit_tests();
  return 0;
#endif
  int N;
  std::cin >> N;
  char v[101], c[101];
  std::cin >> v >> c;
  int s = 0;
  for (int i = 0; i < N; ++i) {
    if (v[i] != '.' && v[i] != c[i]) ++s;
  }
  std::cout << s << std::endl;
  return 0;
}
