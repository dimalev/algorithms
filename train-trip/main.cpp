#include <iostream>
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

void fill(std::map<int, std::set<int>> &lines, const int n,
          const int from, int *d) {
  std::queue<int> input;
  input.push(from);
  std::fill_n(d, n, std::numeric_limits<int>::max());
  d[from] = 0;
  int left = n - 1;
  while(!input.empty() && left > 0) {
    int top = input.front();
    input.pop();
    int l = d[top];
    for(auto k : lines[top]) {
      if(d[k] > l + 1) {
        input.push(k);
        d[k] = l + 1;
        --left;
      }
    }
  }
}

void solve() {
  int n, c[3], v[3];
  std::cin >> n;
  std::cin >> c[0] >> c[1] >> c[2];
  std::cin >> v[0] >> v[1] >> v[2];
  --v[0]; --v[1]; --v[2];
  std::map<int, std::set<int>> lines;
  fr(i,0,n-1) {
    int u,v;
    std::cin >> u >> v;
    --u; --v;
    lines[u].insert(v);
    lines[v].insert(u);
  }
  int *d = new int[n], **V = new int*[3];
  fill(lines, n, 0, d);
  fr(i,0,3) {
    V[i] = new int[n];
    fill(lines, n, v[i], V[i]);
  }
  long best = (d[v[0]] + d[v[1]] + d[v[2]]) * c[0];
  TRACE_LINE(v[1] << ":");
  fr(i,0,n) TRACE_LINE(V[1][i]);
  fr(i, 1, n) {
    long next = d[i] * c[2] + (V[0][i] + V[1][i] + V[2][i]) * c[0];
    // TRACE_LINE("all meet in " << i << ": " << next);
    if(next < best) {
      best = next;
    }
    int *d2 = new int[n];
    fill(lines, n, i, d2);
    fr(j,0,3) {
      next = d[i] * c[1] + (V[0][i] + V[1][i] + V[2][i]) * c[0]
          - (V[j][i] - V[j][0]) * c[0];
      // TRACE_LINE("two meet in " << i << " while " << j << " goes alone: " << next);
      if(next < best) {
        best = next;
      }
      fr(k,1,n) {
        if(k == i) continue;
        next = d[k] * c[2] + d2[k] * c[1]
            + (V[0][i] + V[1][i] + V[2][i]) * c[0]
            - (V[j][i] - V[j][k]) * c[0];
        // TRACE_LINE("two meet in " << i << " and they meet " << j << " in " << k << ": " << next);
        // TRACE_VAR(d[k]);
        // TRACE_VAR(d2[k]);
        // TRACE_VAR(V[0][i]);
        // TRACE_VAR(V[1][i]);
        // TRACE_VAR(V[2][i]);
        // TRACE_VAR(V[j][k]);
        if(next < best) {
          best = next;
        }
      }
    }
    delete[] d2;
  }
  std::cout << best << std::endl;
  delete[] d;
  fr(i,0,3) {
    delete[] V[i];
  }
  delete[] V;
}

int main() {
#ifdef UNITS
  unit_tests();
  return 0;
#endif
  int T;
  std::cin >> T;
  fr(t,0,T) solve();
  return 0;
}
