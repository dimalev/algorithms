#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>

#define fr(v,s,e) for(long long v = s; v < e; ++v)
#define fl(v,s,e) for(long long v = s; v > e; --v)

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
  long long rows, cols, fires_count;
  std::cin >> rows >> cols >> fires_count;
  std::vector<std::pair<long long, long long>> fires;
  fires.resize(fires_count);
  fr(i,0,fires_count) {
    long long r, c;
    std::cin >> r >> c;
    fires[i].first = r - 1;
    fires[i].second = c - 1;
  }
  long long l = -1, r = std::max(rows, cols);
  while(l + 1 < r) {
    long long m = (l + r) / 2;
    std::set<long long> R, C;
    R.insert(0); R.insert(rows);
    C.insert(0); C.insert(cols);
    fr(i,0,fires_count) {
      R.insert(std::max(0ll, fires[i].first - m));
      R.insert(std::min(rows, fires[i].first + m + 1));
      C.insert(std::max(0ll, fires[i].second - m));
      C.insert(std::min(cols, fires[i].second + m + 1));
    }
    TRACE_LINE("m = " << m);
    std::map<long long, long long> Ri, Ci;
    long long Rv[R.size()], Cv[C.size()];
    long long it = 0;
    for(auto v : R) {
      Rv[it] = v;
      Ri[v] = it;
      ++it;
    }
    it = 0;
    for(auto v : C) {
      Cv[it] = v;
      Ci[v] = it;
      ++it;
      TRACE("\t" << v);
    }
    TRACE_LINE("");
    bool on_fire[R.size()][C.size()];
    std::fill_n((bool*)on_fire, R.size() * C.size(), false);
    fr(i,0,fires_count) {
      long long start_r = Ri[std::max(0ll, fires[i].first - m)];
      long long end_r = Ri[std::min(rows, fires[i].first + m + 1)];
      long long start_c = Ci[std::max(0ll, fires[i].second - m)];
      long long end_c = Ci[std::min(cols, fires[i].second + m + 1)];
      fr(r,start_r,end_r)
        fr(c,start_c,end_c)
          on_fire[r][c] = true;
    }
    long long min_r = rows, max_r = 0, min_c = cols, max_c = 0;
    fr(r,0,R.size() - 1) {
      TRACE(Rv[r]);
      fr(c,0,C.size() - 1) {
        TRACE("\t" << (on_fire[r][c] ? "F" : "."));
        if(!on_fire[r][c]) {
          if(r < min_r) min_r = r;
          if(r > max_r) max_r = r;
          if(c < min_c) min_c = c;
          if(c > max_c) max_c = c;
        }
      }
      TRACE_LINE("");
    }
    TRACE_LINE(Rv[R.size() - 1]);
    TRACE_LINE(min_r << " - " << max_r << ", " << min_c << " - " << max_c);
    if(min_r > max_r) {
      r = m;
    } else {
      long long dr = Rv[max_r + 1] - Rv[min_r], dc = Cv[max_c + 1] - Cv[min_c];
      TRACE_LINE(dr << ", " << dc);
      long long max_d = std::max(dr, dc) / 2;
      if(max_d <= m) r = m;
      else l = m;
    }
    TRACE_LINE("");
  }
  std::cout << r << std::endl;
  return 0;
}
