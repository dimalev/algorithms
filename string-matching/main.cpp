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

constexpr int MAX_N = 100000;
constexpr int BUFFER_SIZE = 1000;

int main() {
#ifdef UNITS
  unit_tests();
  return 0;
#endif
  int N;
  std::cin >> N;
  char needle[MAX_N + 1];
  int prefix[MAX_N];
  std::cin.ignore(1e6, '\n');
  std::cin >> needle;
  prefix[0] = -1;
  int current_prefix = -1;
  for(int i = 1; i < N; ++i) {
    ++current_prefix;
    TRACE_LINE(i << " at " << needle[i] << " vs " <<
               needle[current_prefix] << " at " << current_prefix);
    while(current_prefix > 0 && needle[i] != needle[current_prefix]) {
      current_prefix = prefix[current_prefix - 1] + 1;
    }
    if(needle[i] != needle[current_prefix]) {
      current_prefix = -1;
    }
    prefix[i] = current_prefix;
    TRACE_LINE(current_prefix);
  }
  int M;
  std::cin >> M;
  std::cin.ignore(1e7, '\n');
  char hay[BUFFER_SIZE];
  int move = 0, matched_size = -1;
  hay[0] = '\0';
  for(int i = 0; i < M; ++i) {
    if(hay[i - move] == '\0') {
      std::cin.get(hay, BUFFER_SIZE);
      move = i;
    }
    ++matched_size;
    TRACE_LINE(i << " with " << hay[i - move] << " vs " <<
               needle[matched_size] << " at " << matched_size);
    while(matched_size > 0 && needle[matched_size] != hay[i - move]) {
      matched_size = prefix[matched_size - 1] + 1;
    }
    if(needle[matched_size] != hay[i - move]) {
      matched_size = -1;
    }
    if(matched_size == N - 1) {
      std::cout << (i - matched_size) << std::endl;
      return 0;
    }
  }
  std::cout << -1 << std::endl;
  return 0;
}
