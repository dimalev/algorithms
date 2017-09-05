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

int N;
long long S[5001];

int main() {
#ifdef UNITS
  unit_tests();
  return 0;
#endif
  std::cin >> N;
  S[0] = 0ll;
  fr(i,0,N) {
    long long v;
    std::cin >> v;
    S[i + 1] = S[i] + v;
  }
  long long max_total = S[N];
  int d1 = 0, d2 = 0, d3 = N;
  fr(i,0,N+1) {
    long long max_left = S[i];
    int max_d1 = i;
    fr(j,0,i+1) {
      long long left = S[j];
      long long right = S[i] - S[j];
      TRACE_LINE("left: 0 " << j << " " << i << ": " << (left - right));
      if(left - right >= max_left) {
        max_left = left - right;
        max_d1 = j;
      }
    }
    long long max_right = S[N] - S[i];
    long long max_d3 = N;
    fr(j,i,N+1) {
      long long left = S[j]-S[i];
      long long right = S[N] - S[j];
      TRACE_LINE("right: " << i << " " << j << " " << N << ": " << (left - right));
      if(left - right >= max_right) {
        max_right = left - right;
        max_d3 = j;
      }
    }
    if(max_left + max_right >= max_total) {
      max_total = max_left + max_right;
      d1 = max_d1;
      d2 = i;
      d3 = max_d3;
    }
  }
  std::cout << d1 << " " << d2 << " " << d3 << std::endl;
  return 0;
}
