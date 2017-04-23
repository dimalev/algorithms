#include <iostream>
#include <iomanip>
#include <algorithm>
#include <map>

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else

#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)
#define UNIT_TESTS()

#endif

void solve(long t) {
  long N, Q;
  std::cin >> N >> Q;
  double E[N], S[N];
  long D[N][N];
  for(long i = 0; i < N; ++i) {
    std::cin >> E[i] >> S[i];
  }
  for(long i = 0; i < N; ++i) {
    for(long j = 0; j < N; ++j) {
      std::cin >> D[i][j];
    }
  }
  std::multimap<double, int> H[N];
  TRACE_LINE("test " << t);
  for(int h = 0; h < N; ++h) {
    std::multimap<double, int> closest;
    bool touched[N];
    double ways[N];
    std::fill_n(touched, N, false);
    std::fill_n(ways, N, 0.0);
    touched[h] = true;
    for(int i = 0; i < N; ++i) {
      if(D[h][i] > 0) {
        touched[i] = true;
        ways[i] = D[h][i];
        TRACE_LINE("initial from " << h << " to " << i << " length " << D[h][i]);
        closest.emplace(ways[i], i);
      }
    }
    while(!closest.empty()) {
      auto next_it = closest.begin();
      closest.erase(next_it);
      int next_town = next_it->second;
      double next_way = next_it->first;
      if(ways[next_town] < next_way) continue;
      TRACE_LINE("from " << h << " to " << next_town << " during " << (next_way / S[h]));
      H[h].emplace(next_way / S[h], next_town);
      for(int i = 0; i < N; ++i) {
        if(D[next_town][i] > 0) {
          if(next_way + D[next_town][i] <= E[h]) {
            if(!touched[i] || ways[i] > next_way + D[next_town][i]) {
              touched[i] = true;
              ways[i] = next_way + D[next_town][i];
              closest.emplace(ways[i], i);
            }
          }
        }
      }
    }
  }
  std::cout << "Case #" << t << ":";
  for(int q = 0; q < Q; ++q) {
    int u, v;
    std::cin >> u >> v;
    u -= 1; v -= 1;
    // TRACE_LINE(u << " -> " << v);
    bool touched[N];
    std::fill_n(touched, N, false);
    touched[u] = true;
    double times[N];
    std::fill_n(times, N, 0.0);
    std::multimap<double, int> closest;
    // for(int i = 0; i < N; ++i) {
    for(auto close : H[u]) {
      double time = close.first;
      int town = close.second;
      // TRACE_LINE("horse " << u << " to town " << town << " during " << time)
      touched[town] = true;
      times[town] = time;
      closest.emplace(time, town);
    }
    // }
    while(!closest.empty()) {
      auto next_it = closest.begin();
      closest.erase(next_it);
      double time = next_it->first;
      int town = next_it->second;
      if(times[town] < time) continue;
      if(town == v) {
        std::cout << " " << time;
        break;
      }
      for(auto close : H[town]) {
        double next_time = close.first;
        int next_town = close.second;
        if(!touched[next_town] || next_time + time < times[next_town]) {
          touched[next_town] = true;
          times[next_town] = next_time + time;
          closest.emplace(times[next_town], next_town);
        }
      }
    }
  }
  std::cout << "\n";
}

void unit_tests() {
}

int main() {
  UNIT_TESTS();
  long T;
  std::cin >> T;
  std::cout << std::setprecision(8);
  std::cerr << std::setprecision(8);
  for(long t = 1; t <= T; ++t) solve(t);
  return 0;
}
