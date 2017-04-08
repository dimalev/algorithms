#include <iostream>
#include <string>

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else

#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)
#define UNIT_TESTS()

#endif

void solve(int t) {
  std::string str_N;
  std::cin >> str_N;
  int i = 1, len = str_N.length();
  while(i < len) {
    if((str_N[i - 1] - '0') > (str_N[i]) - '0') {
      break;
    }
    ++i;
  }
  long output;
  if(i == len) {
    output = std::stol(str_N);
  } else if(str_N[i - 1] != '1') {
    --i;
    while(i > 0) {
      if(str_N[i - 1] != str_N[i]) {
        break;
      }
      --i;
    }
    str_N[i] = '0' + ((str_N[i] - '0') - 1);
    ++i;
    for(; i < len; ++i) {
      str_N[i] = '9';
    }
    output = std::stol(str_N);
  } else {
    output = 9;
    for(int i = 0; i < len - 2; ++i) {
      output = 10 * output + 9;
    }
  }
  std::cout << "Case #" << t << ": " << output << "\n";
}

void unit_tests() {
}

int main() {
  UNIT_TESTS();
  int T;
  std::cin >> T;
  for(int i = 1; i <= T; ++i) {
    solve(i);
  }
  return 0;
}
