#include <iostream>
#include <cassert>
#include <limits>
#include <map>
#include <set>
#include <queue>

#define fr(v,s,e) for(int v = s; v < e; ++v)
#define fl(v,s,e) for(int v = s; v > e; --v)

#ifdef UNITS
#include "../test/units.cpp"
#endif

#ifdef ALGO_DEBUG
#define TRACE_VAR(var) std::cerr << #var << " = " << var << std::endl
#include "../test/debug.cpp"
#else
#define TRACE_VAR(var)
#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)
#endif

#ifdef UNITS
void unit_tests() {
  test_header("test units");
}
#endif

void single(std::map<long, std::set<long>> &lines, long n, long cost,
            long start, long* distance) {
  std::fill_n(distance, n, -1l);
  std::queue<long> input;
  input.push(start);
  distance[start] = 0;
  while(!input.empty()) {
    long top = input.front();
    input.pop();
    long l = distance[top];
    for(auto k : lines[top]) {
      if(distance[k] == -1) {
        input.push(k);
        distance[k] = l + cost;
      }
    }
  }
}

void two(std::map<long, std::set<long>> &lines, long n, long cost,
            long *one, long *two, long* distance) {
  std::set<int> nodes;
  fr(i,0,n) {
    nodes.insert(i);
    distance[i] = one[i] + two[i];
  }
  while(!nodes.empty()) {
    auto another_it = nodes.begin();
    int another = *another_it;
    nodes.erase(another_it);
    long best = distance[another];
    for(auto close : lines[another]) {
      best = std::min(best, distance[close] + cost);
    }
    if(best < distance[another]) {
      distance[another] = best;
      for(auto close : lines[another])
        nodes.insert(close);
    }
  }
}

void solve() {
  long n, c[3], v[3];
  std::cin >> n;
  std::cin >> c[0] >> c[1] >> c[2];
  std::cin >> v[0] >> v[1] >> v[2];
  --v[0]; --v[1]; --v[2];
  std::map<long, std::set<long>> lines;
  fr(i,0,n-1) {
    long u,v;
    std::cin >> u >> v;
    --u; --v;
    lines[u].insert(v);
    lines[v].insert(u);
  }
  long *V[3];
  fr(i,0,3) {
    V[i] = new long[n];
    single(lines, n, c[0], v[i], V[i]);
  }
  long *V2[3];
  fr(i,0,3) {
    V2[i] = new long[n];
    two(lines, n, c[1], V[(i + 1) % 3], V[(i + 2) % 3], V2[i]);
  }
  long B[n];
  std::set<long> nodes;
  fr(i,0,n) {
    nodes.insert(i);
    B[i] = V[0][i] + V[1][i] + V[2][i];
    fr(j,0,3) {
      B[i] = std::min(V[j][i] + V2[j][i], B[i]);
    }
  }
  while(!nodes.empty()) {
    auto another_it = nodes.begin();
    long another = *another_it;
    nodes.erase(another_it);
    long best = B[another];
    for(auto close : lines[another]) {
      best = std::min(best, B[close] + c[2]);
    }
    if(best < B[another]) {
      B[another] = best;
      for(auto close : lines[another])
        nodes.insert(close);
    }
  }
  std::cout << B[0] << std::endl;
}

int main() {
#ifdef UNITS
  unit_tests();
  return 0;
#endif
  long T;
  std::cin >> T;
  fr(t,0,T) solve();
  return 0;
}
