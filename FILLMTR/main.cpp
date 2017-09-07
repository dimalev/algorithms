#include <iostream>
#include <algorithm>
#include <queue>
#include <map>
#include <set>

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

void solve(int t) {
  int n, m;
  std::cin >> n >> m;
  std::map<int, std::set<int>> neq, eq;
  bool is_bad = false;
  fr(i,0,m) {
    int a, b, c;
    std::cin >> a >> b >> c;
    --a; --b;
    if(is_bad) continue;
    if(a == b) {
      if(c == 1) {
        is_bad = true;
        continue;
      }
    } else {
      if(c == 0) {
        eq[a].insert(b);
        eq[b].insert(a);
      } else {
        neq[a].insert(b);
        neq[b].insert(a);
      }
    }
  }
  if(is_bad) {
    std::cout << "no\n";
    return;
  }
  int E[n];
  std::fill_n(E, n, -1);
  fr(i,0,n) {
    if(E[i] == -1) {
      std::queue<int> other;
      other.push(i);
      E[i] = 0;
      while(!other.empty()) {
        int v = other.front();
        other.pop();
        for(int u : eq[v]) {
          if(E[u] == -1) {
            E[u] = E[v];
            other.push(u);
          } else {
            if(E[u] != E[v]) {
              is_bad = true;
              break;
            }
          }
        }
        for(int u : neq[v]) {
          if(E[u] == -1) {
            E[u] = !E[v];
            other.push(u);
          } else {
            if(E[u] == E[v]) {
              is_bad = true;
              break;
            }
          }
        }
      }
    }
    if(is_bad) break;
  }
  std::cout << (is_bad ? "no" : "yes") << std::endl;
}

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
  int T;
  std::cin >> T;
  fr(t,0,T) solve(t);
  return 0;
}
