#include <iostream>
#include <vector>
#include <queue>
#include <stack>
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
  int day, owner;
  long long cost;
};

class less_day {
 public:
  bool operator()(const ticket& left, const ticket& right) {
    return left.day < right.day;
  }
};

class greater_day {
 public:
  bool operator()(const ticket& left, const ticket& right) {
    return left.day > right.day;
  }
};

struct fly {
  int day;
  long long cost;
};

#ifdef UNITS
void unit_tests() {
  test_header("test units");
}
#endif

int n, m, k;

int main() {
#ifdef UNITS
  unit_tests();
  return 0;
#endif
  std::priority_queue<ticket, std::vector<ticket>, greater_day> out;
  std::priority_queue<ticket, std::vector<ticket>, less_day> in;
  std::queue<fly> depart, arrive;
  std::cin >> n >> m >> k;
  fr(i,0,m) {
    int d, f, t;
    long long c;
    std::cin >> d >> f >> t >> c;
    if(f == 0) {
      in.push({d, t - 1, c});
    } else {
      out.push({d, f - 1, c});
    }
  }
  int day = 0, count_departed = 0, count_arrived = 0;
  long long departed[n], arrived[n], cost = 0ll;
  std::queue<fly> departs;
  std::stack<fly> arrivals;
  std::fill_n(departed, n, -1);
  TRACE_LINE("===== forward");
  while(!out.empty()) {
    ticket next_ticket = out.top();
    TRACE_LINE("process day " << next_ticket.day
               << " for " << next_ticket.owner
               << " cost " << next_ticket.cost);
    out.pop();
    if(departed[next_ticket.owner] == -1) {
      ++count_departed;
      cost += next_ticket.cost;
      departed[next_ticket.owner] = next_ticket.cost;
    } else {
      if(next_ticket.cost < departed[next_ticket.owner]) {
        cost -= departed[next_ticket.owner];
        cost += next_ticket.cost;
        departed[next_ticket.owner] = next_ticket.cost;
      }
    }
    day = next_ticket.day;
    while(!out.empty() && out.top().day == day) {
      next_ticket = out.top();
      out.pop();
      if(departed[next_ticket.owner] == -1) {
        ++count_departed;
        cost += next_ticket.cost;
        departed[next_ticket.owner] = next_ticket.cost;
      } else {
        if(next_ticket.cost < departed[next_ticket.owner]) {
          cost -= departed[next_ticket.owner];
          cost += next_ticket.cost;
          departed[next_ticket.owner] = next_ticket.cost;
        }
      }
    }
    if(count_departed == n) {
      TRACE_LINE("depart on " << day << " for " << cost);
      departs.push({day, cost});
    }
  }
  std::fill_n(arrived, n, -1);
  cost = 0ll;
  TRACE_LINE("===== back");
  while(!in.empty()) {
    ticket next_ticket = in.top();
    TRACE_LINE("process day " << next_ticket.day
               << " for " << next_ticket.owner
               << " cost " << next_ticket.cost);
    in.pop();
    if(arrived[next_ticket.owner] == -1) {
      ++count_arrived;
      cost += next_ticket.cost;
      arrived[next_ticket.owner] = next_ticket.cost;
    } else {
      if(next_ticket.cost < arrived[next_ticket.owner]) {
        cost -= arrived[next_ticket.owner];
        cost += next_ticket.cost;
        arrived[next_ticket.owner] = next_ticket.cost;
      }
    }
    day = next_ticket.day;
    while(!in.empty() && in.top().day == day) {
      next_ticket = in.top();
      in.pop();
      if(arrived[next_ticket.owner] == -1) {
        ++count_arrived;
        cost += next_ticket.cost;
        arrived[next_ticket.owner] = next_ticket.cost;
      } else {
        if(next_ticket.cost < arrived[next_ticket.owner]) {
          cost -= arrived[next_ticket.owner];
          cost += next_ticket.cost;
          arrived[next_ticket.owner] = next_ticket.cost;
        }
      }
    }
    if(count_arrived == n) {
      TRACE_LINE("arrive on " << day << " for " << cost);
      arrivals.push({day, cost});
    }
  }
  fly from = departs.front(), to = arrivals.top();
  if(departs.empty() || arrivals.empty()) {
    std::cout << -1 << std::endl;
    return 0;
  }
  departs.pop(); arrivals.pop();
  while(!arrivals.empty() && to.day - from.day - 1 < k) {
    to = arrivals.top(); arrivals.pop();
  }
  long long min_cost = -1ll;
  if(to.day - from.day - 1 >= k) {
    min_cost = to.cost + from.cost;
    TRACE_LINE("arrive " << to.day << " depart " << from.day << " cost: " << min_cost);
  }
  while(!departs.empty()) {
    from = departs.front(); departs.pop();
    while(!arrivals.empty() && to.day - from.day - 1 < k) {
      to = arrivals.top();
      arrivals.pop();
    }
    if(to.day - from.day - 1 >= k && min_cost > to.cost + from.cost) {
      min_cost = to.cost + from.cost;
      TRACE_LINE("arrive " << to.day << " depart " << from.day << " cost: " << min_cost);
    }
  }
  std::cout << min_cost << std::endl;
  return 0;
}
