#include <iostream>
#include <cstring>

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else

#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)

#endif

const int MAX_S = 10001;

char A[MAX_S];
char B[MAX_S];

int histo[26];

int main() {
  std::cin >> A >> B;
  int S1 = std::strlen(A);
  for(int i = 0; i < S1; ++i) ++histo[A[i] - 'a'];
  int S2 = std::strlen(B);
  for(int i = 0; i < S2; ++i) --histo[B[i] - 'a'];
  int total = 0;
  for(int i = 0; i < 26; ++i) total += abs(histo[i]);
  std::cout << total << std::endl;
  return 0;
}
