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
}

int main() {
  UNIT_TESTS();
  constexpr int days = 366 - 3; // friday, saturday, sunday
  constexpr int end = days / 7 * 7; // where we end;
  constexpr int notaccount = days - end + 1;
  int count;
  std::string of, measure;
  std::cin >> count >> of >> measure;
  if(measure == "week") {
    int res = days / 7;
    if(count < notaccount) ++res; // we check end of year
    if(count >= 5) ++res; // we check start of the year;
    std::cout << res << std::endl;
  } else {
    int res = 7;
    if(count == 30) res = 11;
    if(count <= 29) res = 12;
    std::cout << res << std::endl;
  }
  return 0;
}
