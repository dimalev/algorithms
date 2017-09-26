#include <iostream>
#include <algorithm>
#include <vector>
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

using point_t = std::pair<long long, long long>;

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
  int N, M, K;
  std::cin >> N >> M >> K;
  if(K == 0) {
    std::cout << "0\n";
    return 0;
  }
  point_t P[N];
  fr(i,0,N) std::cin >> P[i].first >> P[i].second;
  point_t B[M];
  fr(i,0,M) std::cin >> B[i].first >> B[i].second;
  long long D[N][M];
  long long l = -1ll, r = 0ll;
  fr(i,0,N) {
    fr(j,0,M) {
      long long dx = P[i].first - B[j].first;
      long long dy = P[i].second - B[j].second;
      D[i][j] = dx * dx + dy * dy;
      if(D[i][j] > r) r = D[i][j];
    }
  }
  int source = 0, sink = N + M + 1;
  while(r - l > 1) {
    long long m = (r + l) >> 1;
    TRACE_LINE(l << " " << m << " " << r);
    std::map<int, std::set<int>> v;
    fr(i,0,N) {
      v[source].insert(i + 1);
      fr(j,0,M) {
        if(i == 0) v[N + j + 1].insert(sink);
        if(D[i][j] <= m) {
          v[i + 1].insert(N + j + 1);
          TRACE_LINE("(+) " << i << " " << j << " l=" << D[i][j]);
        } else TRACE_LINE("(-) " << i << " " << j << " l=" << D[i][j]);
      }
    }
    bool found = false;
    int count = 0;
    std::map<int, std::set<int>> c;
    while(true) {
      std::vector<int> l(N + M + 2);
      std::fill(l.begin(), l.end(), 0);
      std::queue<int> next;
      next.push(source);
      l[source] = source;
      int end = -1;
      while(!next.empty()) {
        int node = next.front();
        next.pop();
        // forward connections
        for(int node2 : v[node]) {
          TRACE_LINE("push> " << node << " -> " << node2);
          if(l[node2] == 0) {
            l[node2] = node;
            if(node2 == sink) {
              end = node2;
              break;
            }
            next.push(node2);
          }
        }
        if(end >= 0) break;
        // backward connections
        for(int node2 : c[node]) {
          TRACE_LINE("push< " << node << " -> " << node2);
          if(l[node2] == 0) {
            l[node2] = node;
            if(node2 == sink) {
              end = node2;
              break;
            }
            next.push(node2);
          }
        }
        if(end >= 0) break;
      }
      if(end < 0) {
        TRACE_LINE("no more pairs");
        break; // no more connections
      }
      // TRACE_LINE(source << ":" << sink << " >> ");
      while(end != source) {
        // TRACE(end << " ");
        int next_end = l[end];
        if(next_end < end) {
          c[end].insert(next_end);
          v[next_end].erase(end);
          if(end > source && end < sink &&
             next_end > source && next_end < sink) ++count;
        } else {
          c[next_end].erase(end);
          v[end].insert(next_end);
          if(end > source && end < sink &&
             next_end > source && next_end < sink) --count;
        }
        end = next_end;
      }
      // TRACE_LINE("");
      TRACE_LINE("total: " << count);
      if(count >= K) {
        found = true;
        break;
      }
    }
    if(found) r = m; else l = m;
  }
  std::cout << r << std::endl;
  return 0;
}
