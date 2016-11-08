#include <iostream>
#include <array>
#include <vector>

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else

#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)

#endif

constexpr char FIRST_LETTER = 'a';
constexpr char LAST_LETTER = 'z';
constexpr int LETTERS = LAST_LETTER - FIRST_LETTER + 1;

void solve() {
  std::string one, two;
  std::cin >> one >> two;
  std::array<std::vector<int>, LETTERS> indexes;
  int one_size = one.size(), two_size = two.size();
  for(int i = 0; i < one_size; ++i)
    indexes[one[i] - FIRST_LETTER].push_back(i);
  for(int i = 0; i < two_size; ++i)
    indexes[two[i] - FIRST_LETTER].push_back(one_size + i);
}

int main() {
  int T;
  std::cin >> T;
  while(T--) solve();
  return 0;
}
