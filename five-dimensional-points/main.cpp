#include <iostream>
#include <array>
#include <vector>
#include <algorithm>

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

int main() {
#ifdef UNITS
  unit_tests();
  return 0;
#endif
  int N;
  std::cin >> N;
  std::vector<std::array<long long, 5>> points;
  points.resize(N);
  fr(i,0,N) {
    fr(j,0,5) {
      std::cin >> points[i][j];
    }
  }
  std::vector<bool> good;
  good.resize(N);
  std::fill(good.begin(), good.end(), true);
  fr(i,0,N) {
    if(!good[i]) continue;
    fr(j,0,N) {
      if(j == i) continue;
      fr(k,0,N) {
        if(k == i || k == j) continue;
        long long v = 0;
        fr(l,0,5)
          v += (points[j][l] - points[i][l]) * (points[k][l] - points[i][l]);
        //TRACE_LINE(i << ": " << j << ", " << k << ": " << v);
        if(v <= 0) {
          good[j] = good[k] = false;
        } else {
          good[i] = false;
          break;
        }
      }
      if(!good[i]) break;;
    }
  }
  int c = 0;
  fr(i,0,N) if(good[i]) ++c;
  std::cout << c << "\n";
  if(c == 0) return 0;
  bool is_first = true;
  fr(i,0,N) if(good[i]) {
    if(!is_first) std::cout << " ";
    std::cout << (i+1);
    is_first = false;
  }
  std::cout << std::endl;
  return 0;
}
