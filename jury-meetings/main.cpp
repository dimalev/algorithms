#include <iostream>
#include <vector>
#include <queue>
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

struct ticket {
  int day;
  long long cost;
};

bool less_day(const ticket& left, const ticket& right) {
  return left.day < right.day;
}

#ifdef UNITS
void unit_tests() {
  test_header("test units");
}
#endif

int n, m, k;

void fill(const std::vector<std::vector<ticket>> &tickets, long long (&costs)[10000]) {
  int index[100000];
  std::priority_queue<std::pair<int, int>> next;
  int day = 0;
  long long cost = 0ll;
  fr(i,0,n) {
    index[i] = 0;
    day = std::max(day, tickets[i][0].day);
    cost += tickets[i][0].cost;
    if(tickets[i].size() > 1) {
      next.emplace(tickets[i][1].day, i);
    }
  }
  while(!next.empty() && next.top().first <= day) {
    auto pair = next.top();
    next.pop();
    int j = pair.second;
    cost -= tickets[j][index[j]].cost;
    index[j]++;
    cost += tickets[j][index[j]].cost;
    if(tickets[j].size() > index[j] + 1) {
      next.emplace(tickets[j][index[j] + 1].day, j);
    }
  }
  TRACE_LINE(day << ": " << cost);
  while(!next.empty()) {
    auto pair = next.top();
    int next_day = pair.first;
    fr(i,day,next_day) costs[i] = cost;
    TRACE_LINE(day << ": " << cost);
    while(!next.empty() && next.top().first <= next_day) {
      auto pair = next.top();
      next.pop();
      int j = pair.second;
      cost -= tickets[j][index[j]].cost;
      index[j]++;
      cost += tickets[j][index[j]].cost;
      if(tickets[j].size() > index[j] + 1) {
        next.emplace(tickets[j][index[j] + 1].day, j);
      }
    }
    day = next_day;
  }
  fr(i,day,10000) costs[i] = cost;
}

int main() {
#ifdef UNITS
  unit_tests();
  return 0;
#endif
  std::vector<std::vector<ticket>> out, in;
  std::cin >> n >> m >> k;
  in.resize(n + 1); out.resize(n + 1);
  fr(i,0,m) {
    int d, f, t;
    long long c;
    std::cin >> d >> f >> t >> c;
    if(f == 0) {
      out[t].push_back({d, c});
    } else in[f].push_back({d, c});
  }
  fr(i,0,n) {
    if(in[i].size() == 0 || out[i].size() == 0) {
      std::cout << -1 << std::endl;
      return 0;
    }
    std::sort(in[i].begin(), in[i].end(), less_day);
    fr(j,1,n) {
      if(in[i][j].cost > in[i][j - 1].cost)
        in[i][j].cost = in[i][j - 1].cost;
    }
    std::sort(out[i].begin(), out[i].end(), less_day);
    fr(j,1,n) {
      if(out[i][j].cost > out[i][j - 1].cost)
        out[i][j].cost = out[i][j - 1].cost;
    }
  }
  long long cost_in[10000], cost_out[10000];
  std::fill_n(cost_in, 10000, -1ll);
  std::fill_n(cost_out, 10000, -1ll);
  fill(in, cost_in);
  fill(out, cost_out);

  long long res = -1ll;
  fr(i,0,1000000-k) {
    if(cost_in[i] > 0 && cost_out[i + k - 1] > 0) {
      if(res == -1 || res > cost_in[i] + cost_out[i + k - 1])
        res = cost_in[i] + cost_out[i + k - 1];
    }
  }
  std::cout << res << std::endl;
  return 0;
}
