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

// bool wins(int A[2], int a) {
//   if(a == 1) {
//     if(A[1] % 2 == 1) return true; // we take all the numbers
//     if(A[1] == 0) return false;
//   } else {
//     if(A[1] % 2 == 0) return true; // we take all the numbers
//     return false;
//   }
// }

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
  fr(i,0,N) {
    int v;
    std::cin >> v;
    if(v % 2 == 1) {
      std::cout << "First\n";
      return 0;
    }
  }
  std::cout << "Second\n";
  return 0;
}
