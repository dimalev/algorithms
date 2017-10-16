#include <iostream>
#include <cassert>
#include <vector>

using ll = long long;

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

int goodSolver(const std::vector <unsigned int> &a) {
  int res = -1, min = 1e5 + 1;
  int n = a.size();
  fr(i,0,n) {
    if(a[i] <= 0) TRACE_LINE("bad: " << a[i] << " at " << i);
    assert(a[i] <= 100000);
    assert(a[i] > 0);
    if(a[i] < min) {
      min = a[i];
      res = i;
    }
  }
  return res + 1;
}

int wrongSolver(const std::vector <unsigned int> a) {
	int n = a.size();
	std::vector<unsigned int> prefSum(n), sufSum(n);
	prefSum[0] = a[0];
	for (int i = 1; i < n; i++) {
		prefSum[i] = prefSum[i - 1] + a[i];
	}
	sufSum[n - 1] = a[n - 1];
	for (int i = n - 2; i >= 0; i--) {
		sufSum[i] = sufSum[i + 1] + a[i];
	}
	unsigned int mn = prefSum[0] + sufSum[0];
  // TRACE_LINE("init: " << mn << " at 1");
	int where = 1;
	for (int i = 1; i < n; i++) {
		unsigned int val = prefSum[i] + sufSum[i];
		if (val < mn) {
      // TRACE_LINE("less: " << val << " at " << (where+1));
			mn = val;
			where = i + 1;
		}
	}
	return where;
}



#ifdef UNITS
void unit_tests() {
  test_header("test units");
}
#endif

constexpr ll limit = (1ll<<32) - 1;

int main() {
#ifdef UNITS
  unit_tests();
  return 0;
#endif
  int T;
  std::cin >> T;
  while(T--) {
    int N;
    std::cin >> N;
  // fr(N,50000,100000) {
    if(N % 10000 == 0) TRACE_LINE("=== " << N);
    std::vector<unsigned int> out;
    out.reserve(N);
    ll count = N+1, seed = (limit / count), seed2 = seed + 1, count2 = 0;
    ll limit1 = seed * count;
    // TRACE_LINE("limit1: " << limit1);
    ll delta = limit - limit1;
    // TRACE_LINE("delta: " << delta);
    while(delta + 5 >= seed || seed + delta + 5 >= 100000) {
      count2 += count / 4;
      limit1 += count / 4;
      count -= count / 4;
      // TRACE_LINE("limit1: " << limit1);
      delta = limit - limit1;
      // TRACE_LINE("delta: " << delta);
    }
    // TRACE_LINE("seeds: " <<
    //            seed << "*" << (count-3) << " " <<
    //            seed2 << "*" << count2);
    // unsigned int sum = 0;
    fr(i,0,count - 3) {
      std::cout << seed << " ";
      // out.push_back(seed);
      // sum += seed;
    }
    fr(i,0,count2) {
      std::cout << seed2 << " ";
      // out.push_back(seed2);
      // sum += seed2;
    }
    std::cout << (seed + delta + 1) << " " << (seed - delta - 1) << "\n";
    // out.push_back(seed + delta + 1);
    // out.push_back(seed - delta - 1);
    // assert(out.size() == N);
    // sum += seed + delta + 1;
    // sum += seed - delta - 1;
    // TRACE_LINE("total sum: " << sum);
    // sum += seed + delta + 1;
    // TRACE_LINE("bigger sum: " << sum);
    // if(seed + delta + 1 <= 0 || seed + delta + 1 >= 100000) {
    //   TRACE_LINE("out of bounds " << N);
    // }
    // if(seed - delta - 1 <= 0 || seed - delta - 1 >= 100000) {
    //   TRACE_LINE("out of bounds " << N);
    // }
    // TRACE_LINE(goodSolver(out) << " VS " << wrongSolver(out));
    // if(goodSolver(out) == wrongSolver(out)) {
    //   TRACE_LINE("WA: " << N);
    //   return -1;
    // }
  }
  return 0;
}
